//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"
#include "Environment.h"


///Initialize static members
uint32_t Memory::sram_start = 0;
uint32_t Memory::sram_ended = 0;
uint32_t Memory::sram_used = 0;
uint32_t Memory::sbrk_heap = 0;
Memory::MapNode* Memory::head = NULL;
Memory::MapNode* Memory::tail = NULL;


///Memory initialize sram parameters
void Memory::Initialize()
{
	//Initialize list, align 4 bytes
	head = new MapNode(Map(sram_start, 4));
	tail = new MapNode(Map(sram_ended, 4));
	head->next = tail;
	tail->prev = head;
}


///Memory heap alloc
uint32_t Memory::HeapAlloc(uint32_t size)
{
	MapNode** currNode = &head;
	MapNode** nextNode = &head;
	uint32_t  nextMapAddr = 0;
	uint32_t  nextEndAddr = 0;

	//Find free space
	while (NULL != *nextNode)
	{
		nextMapAddr = (*currNode)->map.addr + (*currNode)->map.size;
		nextEndAddr = nextMapAddr + size;

		//There is free space between the current node and the next node
		if (nextEndAddr <= (*nextNode)->map.addr)
		{
			//Update the used size of sram
			sram_used += size;

			//Add map node into list
			MapNode* tmpNode = *nextNode;
			*nextNode = new MapNode(Map(nextMapAddr, size));
			(*nextNode)->prev =  tmpNode->prev;
			  tmpNode  ->prev = *nextNode;
			(*nextNode)->next =  tmpNode;
			return (*nextNode)->map.addr;
		}
		else
		{
			currNode = nextNode;
			nextNode = &(*nextNode)->next;
		}
	}

	return 0;
}
EXPORT_SYMBOL(Memory::HeapAlloc, _ZN6Memory9HeapAllocEm);


///Memory stack alloc
uint32_t Memory::StackAlloc(uint32_t size)
{
	MapNode** prevNode = &tail;
	MapNode** currNode = &tail;
	uint32_t  prevMapAddr = 0;
	uint32_t  prevEndAddr = 0;

	//Find free space
	while (NULL != *prevNode)
	{
		prevMapAddr = (*currNode)->map.addr - (*currNode)->map.size;
		prevEndAddr = prevMapAddr - size;

		//There is free space between the current node and the prev node
		if (prevEndAddr >= (*prevNode)->map.addr)
		{
			//Update the used size of sram
			sram_used += size;

			//Add map node into list
			MapNode* tmpNode = *prevNode;
			*prevNode = new MapNode(Map(prevMapAddr, size));
			(*prevNode)->next =  tmpNode->next;
			  tmpNode  ->next = *prevNode;
			(*prevNode)->prev =  tmpNode;
			return (*prevNode)->map.addr;
		}
		else
		{
			currNode = prevNode;
			prevNode = &(*prevNode)->prev;
		}
	}

	return 0;
}
EXPORT_SYMBOL(Memory::StackAlloc, _ZN6Memory10StackAllocEm);


///Memory free
void Memory::Free(uint32_t memory)
{
	MapNode** prevNode = &head;
	MapNode** currNode = &head;

	while (NULL != *currNode)
	{
		if (memory == (*currNode)->map.addr)
		{
			//Update the used size of sram
			sram_used -= (*currNode)->map.size;

			//Remove map node from list
			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}
EXPORT_SYMBOL(Memory::Free, _ZN6Memory4FreeEm);


///Memory sbrk
uint32_t Memory::Sbrk(int32_t incr)
{
	//Initialize heap end at first call
	if (0 == sbrk_heap)
	{
		//Symbol defined in the linker script
		extern void* _ebss;
		extern void* _estack;

		//Calculate sram start and end address
		sram_start = (uint32_t)&_ebss   + user_rsvd_heap;
		sram_ended = (uint32_t)&_estack - user_rsvd_stack;

		//Calculate the used size of sram
		sram_used  = user_rsvd_heap + user_rsvd_stack;

		//Calculate sbrk stack address
		sbrk_heap  = (uint32_t)&_ebss;
	}

	//Protect heap from growing into the reserved MSP stack
	if (sbrk_heap + incr > sram_start)
	{
		//halt on here
		while(1) {}
	}

	//Calculate sbrk heap end
	sbrk_heap += incr;

	//updata the used siez of sram
	sram_used += incr;

	return (sbrk_heap - incr);
}


///Override _sbrk
extern "C" void* _sbrk(ptrdiff_t incr)
{
	return (void*)Memory::Sbrk((int32_t)incr);
}
