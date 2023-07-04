//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"
#include "Debug.h"
#include "Environment.h"


/// @brief Constructor
Memory::Memory()
	:sram_start(0),
	sram_ended(0),
	sram_used(0),
	sbrk_heap(0),
	head(NULL),
	tail(NULL)
{
	Initialize();
}


/// @brief Fini constructor
Memory::~Memory()
{
}


/// @brief Singleton Instance
/// @return Memory instance
Memory& Memory::Instance()
{
	static Memory instance;
	return instance;
}
EXPORT_SYMBOL(_ZN6Memory8InstanceEv);


/// @brief Definitions memory
Memory& memory = Memory::Instance();


/// @brief Memory initialize sram parameters
void Memory::Initialize()
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

		//Calculate the used size of sram
		sram_used  = kernel_rsvd_heap + kernel_rsvd_stack;

		//Calculate sbrk stack address
		sbrk_heap  = (uint32_t)&_ebss;
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
	}
}


/// @brief Memory heap alloc
/// @param size heap alloc byte size
/// @return alloc address
uint32_t Memory::HeapAlloc(uint32_t size)
{
	MapNode* newNode  = NULL;
	MapNode* currNode = head;
	MapNode* nextNode = head->next;
	uint32_t nextMapSize = 0;
	uint32_t nextMapAddr = 0;
	uint32_t nextEndAddr = 0;

	//Find free space
	while (NULL != nextNode)
	{
		//Calculate the next map size
		nextMapSize = size_of_node + size;

		//Align memory by aligning allocation sizes
		if (nextMapSize % align) nextMapSize += (align - (nextMapSize % align));

		//Calculate the next map and end addr
		nextMapAddr = currNode->map.addr + currNode->map.size;
		nextEndAddr = nextMapAddr + nextMapSize;

		//There is free space between the current node and the next node
		if (nextEndAddr <= nextNode->map.addr)
		{
			//Output debug info
			debug.Output(Debug::_Lv0, "heap alloc: addr = 0x%08lx, size = %ld\r\n", nextMapAddr, nextMapSize);

			//Update the used size of sram
			sram_used += nextMapSize;

			//Add map node into list
			newNode           = (MapNode*)(nextMapAddr);
			newNode->map.addr = nextMapAddr;
			newNode->map.size = nextMapSize;
			newNode->prev     = currNode;
			newNode->next     = nextNode;
			currNode->next    = newNode;
			nextNode->prev    = newNode;
			return newNode->map.addr + size_of_node;
		}
		else
		{
			currNode = nextNode;
			nextNode = nextNode->next;
		}
	}

	return 0;
}
EXPORT_SYMBOL(_ZN6Memory9HeapAllocEm);


/// @brief Memory stack alloc
/// @param size stack alloc byte size
/// @return alloc address
uint32_t Memory::StackAlloc(uint32_t size)
{
	MapNode* newNode  = new MapNode();
	MapNode* prevNode = tail->prev;
	MapNode* currNode = tail;
	uint32_t prevMapSize = 0;
	uint32_t prevMapAddr = 0;
	uint32_t prevEndAddr = 0;

	//Find free space
	while (NULL != prevNode)
	{
		//Calculate the prev map size
		prevMapSize = size;

		//Align memory by aligning allocation sizes
		if (prevMapSize % align) prevMapSize += (align - (prevMapSize % align));

		//Calculate the prev map and end addr
		prevMapAddr = currNode->map.addr - currNode->map.size;
		prevEndAddr = prevMapAddr - prevMapSize;

		//There is free space between the current node and the prev node
		if (prevEndAddr >= prevNode->map.addr)
		{
			//Output debug info
			debug.Output(Debug::_Lv0, "stack alloc: addr = 0x%08lx, size = %ld\r\n", prevMapAddr, prevMapSize);

			//Update the used size of sram
			sram_used += prevMapSize;

			//Add map node into list
			newNode->map.addr = prevMapAddr;
			newNode->map.size = prevMapSize;
			newNode->prev     = prevNode;
			newNode->next     = currNode;
			currNode->prev    = newNode;
			prevNode->next    = newNode;
			return newNode->map.addr;
		}
		else
		{
			currNode = prevNode;
			prevNode = prevNode->prev;
		}
	}

	delete newNode;
	return 0;
}
EXPORT_SYMBOL(_ZN6Memory10StackAllocEm);


/// @brief Memory free
/// @param memory free address
/// @param size free byte size
void Memory::Free(uint32_t memory, uint32_t size)
{
	MapNode* currNode = head;

	while (NULL != currNode)
	{
		if ((memory >= currNode->map.addr) && 
			(memory < (currNode->map.addr + currNode->map.size)))
		{
			if (0 == size)
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

			//Update the used size of sram
			sram_used -= currNode->map.size;

			//Output debug info
			debug.Output(Debug::_Lv0, "free memory: addr: 0x%08lx, size: %ld\r\n",
			currNode->map.addr, currNode->map.size);

			break;
		}
		else
		{
			currNode = currNode->next;
		}
	}
}
EXPORT_SYMBOL(_ZN6Memory4FreeEmm);


/// @brief Memory sbrk
/// @param incr increase byte size
/// @return address
uint32_t Memory::Sbrk(int32_t incr)
{
	//Protect heap from growing into the reserved MSP stack
	if (sbrk_heap + incr > sram_start)
	{
		debug.Output(Debug::_Lv0, "error: out of memory.\r\n");
		//halt on here
		while(1) {}
	}

	//Calculate sbrk heap end
	sbrk_heap += incr;

	//updata the used siez of sram
	sram_used += incr;

	return (sbrk_heap - incr);
}


/// @brief Override _sbrk
/// @param incr increase byte size
/// @return address
extern "C" void* _sbrk(ptrdiff_t incr)
{
	return (void*)Memory::Instance().Sbrk((int32_t)incr);
}


/// @brief Memory new method
/// @param size byte size
/// @return address
void* New(uint32_t size)
{
	return (void*)Memory::Instance().HeapAlloc((uint32_t)size);
}
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znwm);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znam);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znwj);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znaj);


/// @brief Memory delete method
/// @param ptr address
void Delete(void* ptr)
{
	Memory::Instance().Free((uint32_t)ptr);
}
EXPORT_SYMBOL_ALIAS(_Z6DeletePv, _ZdaPv);
EXPORT_SYMBOL_ALIAS(_Z6DeletePv, _ZdlPv);


/// @brief Memory delete method
/// @param ptr address
/// @param size byte size
void DeleteSize(void* ptr, uint32_t size)
{
	Memory::Instance().Free((uint32_t)ptr, size);
}
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdaPvm);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdlPvm);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdaPvj);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdlPvj);


/// @brief Override new
/// @param size byte size
/// @return address
void *operator new(size_t size)
{
	return New(size);
}


/// @brief Override new[]
/// @param size byte size
/// @return address
void *operator new[](size_t size)
{
	return New(size);
}


/// @brief Override delete
/// @param ptr address
void operator delete(void *ptr)
{
	Delete(ptr);
}


/// @brief Override delete[]
/// @param ptr address
void operator delete[](void *ptr)
{
	Delete(ptr);
}


/// @brief Override delete
/// @param ptr address
/// @param size byte size
void operator delete(void *ptr, size_t size)
{
	DeleteSize(ptr, size);
}


/// @brief Override delete[]
/// @param ptr address
/// @param size byte size
void operator delete[](void *ptr, size_t size)
{
	DeleteSize(ptr, size);
}


/// @brief malloc
/// @param size 
/// @return 
extern "C" void* malloc(size_t size)
{
	return New(size);
}


/// @brief free
/// @param ptr 
extern "C" void free(void* ptr)
{
	Delete(ptr);
}
