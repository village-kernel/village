//###########################################################################
// vk_memory.h
// Declarations of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MEMORY_H__
#define __VK_MEMORY_H__

#include "vk_kernel.h"
#include "vk_spinlock.h"


#ifndef KERNEL_RSVD_HEAP
#define KERNEL_RSVD_HEAP       1024
#endif

#ifndef KERNEL_RSVD_STACK
#define KERNEL_RSVD_STACK      1024
#endif


/// @brief ConcreteMemory
class ConcreteMemory : public Memory
{
private:
    /// @brief Structures
    struct Map 
    {
        uint32_t addr;
        uint32_t size;

        Map(uint32_t addr = 0, uint32_t size = 0):
            addr(addr),
            size(size)
        {}
    };

    struct MapNode
    {
        Map map;
        MapNode* prev;
        MapNode* next;

        MapNode(Map map = 0):
            map(map),
            prev(NULL),
            next(NULL)
        {}
    };
private:
    /// @brief Static constants
    const static uint8_t  align = 4;
    const static uint32_t size_of_node = sizeof(MapNode);
    const static uint32_t kernel_rsvd_heap  = KERNEL_RSVD_HEAP;
    const static uint32_t kernel_rsvd_stack = KERNEL_RSVD_STACK;

    /// @brief Sram parameters
    bool isMemReady;
    uint32_t sram_start;
    uint32_t sram_ended;
    uint32_t sram_used;
    uint32_t sbrk_heap;

    /// @brief Members
    MapNode* head;
    MapNode* tail;
    MapNode* curr;

    /// @brief Locks
    SpinLock heapLock;
    SpinLock stackLock;
public:
    /// @brief Methods
    ConcreteMemory();
    ~ConcreteMemory();
    void Setup();
    void Exit();

    /// @brief Alloc Methods
    uint32_t HeapAlloc(uint32_t size);
    uint32_t StackAlloc(uint32_t size);
    void Free(uint32_t memory, uint32_t size = 0);

    /// @brief Info Methods
    uint32_t GetSize();
    uint32_t GetUsed();
    uint32_t GetCurrAddr();
};

#endif //!__VK_MEMORY_H__
