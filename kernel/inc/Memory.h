//###########################################################################
// Memory.h
// Declarations of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "stdint.h"
#include "stddef.h"

///Memory
class Memory
{
private:
	//Structures
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

		MapNode(Map map):
			map(map),
			prev(NULL),
			next(NULL)
		{}
	};

	//Static constants
	static const uint32_t reserved_heap = 0x3200;

	//Sram parameters
	static uint32_t sram_start;
	static uint32_t sram_ended;
	static uint32_t sbrk_stack;
	static uint32_t sbrk_heap;

	//Members
	static MapNode* head;
	static MapNode* tail;
public:
	//Methods
	static void Initialize();
	static uint32_t HeapAlloc(uint32_t size);
	static uint32_t StackAlloc(uint32_t size);
	static uint32_t Sbrk(int32_t incr);
	static void Free(uint32_t memory);
};

#endif //!__MEMORY_H__
