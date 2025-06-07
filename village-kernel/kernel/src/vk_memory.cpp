//###########################################################################
// vk_memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_memory.h"


/// @brief Constructor
ConcreteMemory::ConcreteMemory()
    :isMemReady(false),
    sram_start(0),
    sram_ended(0),
    sram_used(0),
    sbrk_heap(0),
    head(NULL),
    tail(NULL),
    curr(NULL)
{
    //Initialize heap end at first call
    if (0 == sbrk_heap)
    {
        //Symbol defined in the linker script
        extern void* _ebss;
        extern void* _estack;

        //Calculate sram start and end address
        sram_start = (uint32_t)&_ebss   + kernel_rsvd_heap;
        sram_ended = (uint32_t)&_estack - kernel_rsvd_stack;

        //Aligning sram_start and sram_ended by align byte
        if (sram_start % align) sram_start += (align - (sram_start % align));
        if (sram_ended % align) sram_ended -= (sram_ended % align);

        //Calculate sbrk stack address
        sbrk_heap = (uint32_t)&_ebss;
    }

    //Initialize list, align 4 bytes
    if (NULL == head || NULL == tail)
    {
        head       = (MapNode*)(sram_start) + 0;
        tail       = (MapNode*)(sram_start) + 1;

        head->map  = Map(sram_start + size_of_node, size_of_node);
        head->prev = NULL;
        head->next = tail;

        tail->map  = Map(sram_ended - size_of_node, size_of_node);
        tail->prev = head;
        tail->next = NULL;

        curr       = head;
    }
}


/// @brief Destructor
ConcreteMemory::~ConcreteMemory()
{
}


/// @brief Memory setup sram parameters
void ConcreteMemory::Setup()
{
    isMemReady = true;

    //Output debug info
    kernel->debug.Info("Memory setup done!");
}


/// @brief Exit
void ConcreteMemory::Exit()
{
    isMemReady = false;
}


/// @brief Memory heap alloc
/// @param size heap alloc byte size
/// @return alloc address
uint32_t ConcreteMemory::HeapAlloc(uint32_t size)
{
    heapLock.Lock();

    MapNode* newNode  = NULL;
    MapNode* currNode = curr;
    MapNode* nextNode = curr->next;
    uint32_t newMapSize = 0;
    uint32_t newMapAddr = 0;
    uint32_t newEndAddr = 0;
    uint32_t allocAddr = 0;

    //Find free space
    while (NULL != nextNode)
    {
        //Calculate the next map size
        newMapSize = size_of_node + size;

        //Calculate the next map
        newMapAddr = currNode->map.addr + currNode->map.size;

        //Align memory by aligning allocation sizes
        if (newMapSize % align) newMapSize += (align - (newMapSize % align));
        
        //Align memory by aligning allocation addr
        if (newMapAddr % align) newMapAddr += (align - (newMapAddr % align));

        //Calculate the end addr
        newEndAddr = newMapAddr + newMapSize;

        //There is free space between the current node and the next node
        if (newEndAddr <= nextNode->map.addr)
        {
            //Output debug info
            if (isMemReady)
            {
                kernel->debug.Output
                (
                    Debug::_Lv0, 
                    "heap alloc: addr = 0x%08lx, size = %ld",
                    newMapAddr,
                    newMapSize
                );
            }

            //Update the used size of sram
            sram_used += newMapSize;

            //Add map node into list
            newNode           = (MapNode*)(newMapAddr);
            newNode->map.addr = newMapAddr;
            newNode->map.size = newMapSize;
            newNode->prev     = currNode;
            newNode->next     = nextNode;
            currNode->next    = newNode;
            nextNode->prev    = newNode;
            curr              = newNode;
            allocAddr         = newNode->map.addr + size_of_node;
            break;
        }
        else
        {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
    }

    //Out of memory
    if (0 == allocAddr)
    {
        if (isMemReady) kernel->debug.Error("out of memory.");
        while(1) {}
    }

    heapLock.Unlock();

    return allocAddr;
}


/// @brief Memory stack alloc
/// @param size stack alloc byte size
/// @return alloc address
uint32_t ConcreteMemory::StackAlloc(uint32_t size)
{
    stackLock.Lock();

    MapNode* newNode  = new MapNode();
    MapNode* prevNode = tail->prev;
    MapNode* currNode = tail;
    uint32_t newMapSize = 0;
    uint32_t newMapAddr = 0;
    uint32_t newEndAddr = 0;
    uint32_t allocAddr = 0;

    //Find free space
    while (NULL != prevNode)
    {
        //Calculate the new map size
        newMapSize = size;

        //Calculate the new map
        newMapAddr = currNode->map.addr - currNode->map.size;

        //Align memory by aligning allocation sizes
        if (newMapSize % align) newMapSize += (align - (newMapSize % align));

        //Align memory by aligning allocation addr
        if (newMapAddr % align) newMapAddr += (align - (newMapAddr % align));

        //Calculate the end addr
        newEndAddr = newMapAddr - newMapSize;

        //There is free space between the current node and the prev node
        if (newEndAddr >= prevNode->map.addr)
        {
            //Output debug info
            if (isMemReady)
            {
                kernel->debug.Output
                (
                    Debug::_Lv0,
                    "stack alloc: addr = 0x%08lx, size = %ld",
                    newMapAddr,
                    newMapSize
                );
            }

            //Update the used size of sram
            sram_used += newMapSize;

            //Add map node into list
            newNode->map.addr = newMapAddr;
            newNode->map.size = newMapSize;
            newNode->prev     = prevNode;
            newNode->next     = currNode;
            currNode->prev    = newNode;
            prevNode->next    = newNode;
            allocAddr         = newNode->map.addr;
            break;
        }
        else
        {
            currNode = prevNode;
            prevNode = prevNode->prev;
        }
    }

    //Out of memory
    if (0 == allocAddr)
    {
        if (isMemReady) kernel->debug.Error("out of memory.");
        while(1) {}
    }

    stackLock.Unlock();
    
    return allocAddr;
}


/// @brief Memory free
/// @param memory free address
/// @param size free byte size
void ConcreteMemory::Free(uint32_t memory, uint32_t size)
{
    if (0 == memory) return;

    MapNode* currNode = curr;

    while (NULL != currNode)
    {
        uint32_t currStartAddr = currNode->map.addr;
        uint32_t currEndedAddr = currNode->map.addr + currNode->map.size;

        //Break when the memory is between the end of the current node 
        //and the beginning of the next node, because it has been released
        if (NULL != currNode->next)
        {
            uint32_t nextStartAddr = currNode->next->map.addr;
            if (memory > currEndedAddr && memory < nextStartAddr) break;
        }

        //Release memory node
        if ((memory >= currStartAddr) && (memory < currEndedAddr))
        {
            if (0 == size || size_of_node == (currNode->map.size - size))
            {
                //Remove map node from list
                currNode->prev->next = currNode->next;
                currNode->next->prev = currNode->prev;
            }
            else
            {
                //Reduce space
                currNode->map.size = currNode->map.size - size;
            }

            //Update current node pointer
            MapNode* newCurr = (currNode->prev) ? currNode->prev : head;
            if (curr->map.addr > newCurr->map.addr) curr = newCurr;

            //Update the used size of sram
            sram_used -= currNode->map.size;

            //Output debug info
            if (isMemReady)
            {
                kernel->debug.Output
                (
                    Debug::_Lv0,
                    "free memory: addr = 0x%08lx, size = %ld",
                    currNode->map.addr,
                    currNode->map.size
                );
            }

            break;
        }
        else
        {
            currNode = (memory < currNode->map.addr) ? currNode->prev : currNode->next;
        }
    }
}


/// @brief Get the max size of sram
uint32_t ConcreteMemory::GetSize() { return sram_ended - sram_start; }


/// @brief Get the used size of sram
uint32_t ConcreteMemory::GetUsed() { return sram_used; }


/// @brief Get the addr of current node
uint32_t ConcreteMemory::GetCurrAddr() { return curr->map.addr; }
