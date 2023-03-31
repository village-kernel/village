//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"
#include "Environment.h"
#include "stdio.h"


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
	//Initialize heap end at first call
	if (0 == sbrk_heap)
	{
		//Symbol defined in the linker script
		extern void* _ebss;
		extern void* _estack;

		//Calculate sram start and end address
		sram_start = (uint32_t)&_ebss   + kernel_rsvd_heap;
		sram_ended = (uint32_t)&_estack - kernel_rsvd_stack;

		//Calculate the used size of sram
		sram_used  = kernel_rsvd_heap + kernel_rsvd_stack;

		//Calculate sbrk stack address
		sbrk_heap  = (uint32_t)&_ebss;
	}

	//Initialize list, align 4 bytes
	if (NULL == head || NULL == tail)
	{
		uint8_t size = sizeof(MapNode);

		head       = (MapNode*)(sram_start) + 0;
		tail       = (MapNode*)(sram_start) + 1;

		head->map  = Map(sram_start + size, size);
		head->prev = NULL;
		head->next = tail;

		tail->map  = Map(sram_ended - size, size);
		tail->prev = head;
		tail->next = NULL;
	}
}


///Memory heap alloc
uint32_t Memory::HeapAlloc(uint32_t size)
{
	Memory::Initialize();

	MapNode* newNode  = NULL;
	MapNode* currNode = head;
	MapNode* nextNode = head->next;
	uint32_t nextMapSize = 0;
	uint32_t nextMapAddr = 0;
	uint32_t nextEndAddr = 0;

	//Find free space
	while (NULL != nextNode)
	{
		nextMapSize = size + sizeof(MapNode);
		nextMapAddr = currNode->map.addr + currNode->map.size;
		nextEndAddr = nextMapAddr + nextMapSize;

		//There is free space between the current node and the next node
		if (nextEndAddr <= nextNode->map.addr)
		{
			//Output debug info
			printf("heap alloc: addr = 0x%08lx, size = %ld\r\n", nextMapAddr, nextMapSize);

			//Update the used size of sram
			sram_used += nextMapSize;

			//Add map node into list
			newNode        = (MapNode*)(nextMapAddr);
			newNode->map   = Map(nextMapAddr, nextMapSize);
			newNode->prev  = currNode;
			newNode->next  = nextNode;
			currNode->next = newNode;
			nextNode->prev = newNode;
			return newNode->map.addr + sizeof(MapNode);
		}
		else
		{
			currNode = nextNode;
			nextNode = nextNode->next;
		}
	}

	return 0;
}
EXPORT_SYMBOL(Memory::HeapAlloc, _ZN6Memory9HeapAllocEm);


///Memory stack alloc
uint32_t Memory::StackAlloc(uint32_t size)
{
	Memory::Initialize();

	MapNode* newNode  = new MapNode();
	MapNode* prevNode = tail->prev;
	MapNode* currNode = tail;
	uint32_t prevMapAddr = 0;
	uint32_t prevEndAddr = 0;

	//Find free space
	while (NULL != prevNode)
	{
		prevMapAddr = currNode->map.addr - currNode->map.size;
		prevEndAddr = prevMapAddr - size;

		//There is free space between the current node and the prev node
		if (prevEndAddr >= prevNode->map.addr)
		{
			//Output debug info
			printf("stack alloc: addr = 0x%08lx, size = %ld\r\n", prevMapAddr, size);

			//Update the used size of sram
			sram_used += size;

			//Add map node into list
			newNode->map   = Map(prevMapAddr, size);
			newNode->prev  = prevNode;
			newNode->next  = currNode;
			currNode->prev = newNode;
			prevNode->next = newNode;
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
EXPORT_SYMBOL(Memory::StackAlloc, _ZN6Memory10StackAllocEm);


///Memory free
void Memory::Free(uint32_t memory)
{
	Memory::Initialize();

	MapNode* currNode = head;

	while (NULL != currNode)
	{
		if ((memory >= currNode->map.addr) && 
			(memory < (currNode->map.addr + currNode->map.size)))
		{
			//Update the used size of sram
			sram_used -= currNode->map.size;

			//Remove map node from list
			currNode->prev->next = currNode->next;
			currNode->next->prev = currNode->prev;

			break;
		}
		else
		{
			currNode = currNode->next;
		}
	}
}
EXPORT_SYMBOL(Memory::Free, _ZN6Memory4FreeEm);


///Memory sbrk
uint32_t Memory::Sbrk(int32_t incr)
{
	Memory::Initialize();

	//Protect heap from growing into the reserved MSP stack
	if (sbrk_heap + incr > sram_start)
	{
		printf("error: out of memory.\r\n");
		//halt on here
		while(1) {}
	}

	//Calculate sbrk heap end
	sbrk_heap += incr;

	//updata the used siez of sram
	sram_used += incr;

	return (sbrk_heap - incr);
}


///Override new
void *operator new(size_t size)
{
	return (void*)Memory::HeapAlloc((uint32_t)size);
}
EXPORT_SYMBOL(Memory::HeapAlloc, _Znwj);


///Override new[]
void *operator new[](size_t size)
{
	return (void*)Memory::HeapAlloc((uint32_t)size);
}
EXPORT_SYMBOL(Memory::HeapAlloc, _Znaj);


///Override delete
void operator delete(void *ptr)
{
	Memory::Free((uint32_t)ptr);
}
EXPORT_SYMBOL(Memory::Free, _ZdaPv);


///Override delete[]
void operator delete[](void *ptr)
{
	Memory::Free((uint32_t)ptr);
}
EXPORT_SYMBOL(Memory::Free, _Zdlpv);


///Override _sbrk
extern "C" void* _sbrk(ptrdiff_t incr)
{
	return (void*)Memory::Sbrk((int32_t)incr);
}
