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

		MapNode(Map map = 0):
			map(map),
			prev(NULL),
			next(NULL)
		{}
	};

	//Static constants
	const static uint32_t size_of_node = sizeof(MapNode);
	const static uint32_t kernel_rsvd_heap  = 0x4000;  //10k
	const static uint32_t kernel_rsvd_stack = 0x3200;  //8k

	//Sram parameters
	static uint32_t sram_start;
	static uint32_t sram_ended;
	static uint32_t sram_used;
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

	//Get the used szie of sram
	static uint32_t GetUsed() { return sram_used; }
};

#endif //!__MEMORY_H__
