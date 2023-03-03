//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"


///Initialize static members
uint32_t Memory::curStack = Memory::end_stack;


///Memory malloc
uint32_t Memory::Malloc(uint32_t size)
{
	curStack = curStack - size;

	return curStack;
}


///Memory free
void Memory::Free(uint32_t memory, uint32_t size)
{
	
}
