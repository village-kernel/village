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
		MapNode* next;

		MapNode(Map map):
			map(map),
			next(NULL)
		{}
	};

	//Static constants
	static const uint32_t start_stack = 0x20000000;
	static const uint32_t start_used_stack = 0x20000800;
	static const uint32_t ended_used_stack = 0x2001bc00;
	static const uint32_t ended_stack = 0x2001c000;

	//Members
	static MapNode* list;
public:
	//Methods
	static uint32_t Malloc(uint32_t size);
	static void Free(uint32_t memory);
};

#endif //!__MEMORY_H__
