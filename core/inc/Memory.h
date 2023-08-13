//###########################################################################
// Memory.h
// Declarations of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Defines.h"

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
	const static uint8_t  align = 4;
	const static uint32_t size_of_node = sizeof(MapNode);
	const static uint32_t kernel_rsvd_heap  = 0x4000;  //10k
	const static uint32_t kernel_rsvd_stack = 0x3200;  //8k

	//Sram parameters
	bool isMemReady;
	uint32_t sram_start;
	uint32_t sram_ended;
	uint32_t sram_used;
	uint32_t sbrk_heap;

	//Members
	MapNode* head;
	MapNode* tail;

	//Methods
	Memory();
	~Memory();
public:
	//Methods
	void Initialize();
	uint32_t HeapAlloc(uint32_t size);
	uint32_t StackAlloc(uint32_t size);
	uint32_t Sbrk(int32_t incr);
	void Free(uint32_t memory, uint32_t size = 0);

	//Get the used szie of sram
	uint32_t GetUsed() { return sram_used; }

	//Singleton Instance
	static Memory& Instance();
};

///Declarations memory reference
extern Memory& memory;

#endif //!__MEMORY_H__
