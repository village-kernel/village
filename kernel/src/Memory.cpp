//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"


///Initialize static members
Memory::MapNode* Memory::list = NULL;


///Memory malloc
uint32_t Memory::Malloc(uint32_t size)
{
	MapNode** currNode = &list;
	MapNode** nextNode = &list;
	uint32_t  nextMapAddr = 0;
	uint32_t  nextEndAddr = 0;

	//Find free space
	while (NULL != *nextNode)
	{
		nextMapAddr = (*currNode)->map.addr - (*currNode)->map.size;
		nextEndAddr = nextMapAddr - size;

		//There is free space between the current node and the next node
		if (nextEndAddr >= (*nextNode)->map.addr)
		{
			MapNode* tmpNode = *nextNode;
			*nextNode = new MapNode(Map(nextMapAddr, size));
			(*nextNode)->next = tmpNode;
			return (*nextNode)->map.addr;
		}
		else
		{
			currNode = nextNode;
			nextNode = &(*nextNode)->next;
		}
	}

	//Calculate next map address
	if (NULL != *currNode)
		nextMapAddr = (*currNode)->map.addr - (*currNode)->map.size;
	else
		nextMapAddr = ended_used_stack;
	
	//Calculate next end address
	nextEndAddr = nextMapAddr - size;

	//Check whether there is free space
	if (nextEndAddr < start_used_stack) return 0;

	//Add next node
	*nextNode = new MapNode(Map(nextMapAddr, size));

	return (*nextNode)->map.addr;
}


///Memory free
void Memory::Free(uint32_t memory)
{
	MapNode** prevNode = &list;
	MapNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (memory == (*currNode)->map.addr)
		{
			delete *currNode;

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
