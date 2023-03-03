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
	//Static constants
	static const uint32_t start_stack = 0x20000000;
	static const uint32_t end_stack = 0x2001c000;

	//Members
	static uint32_t curStack;
public:
	//Methods
	static uint32_t Malloc(uint32_t size);
	static void Free(uint32_t memory, uint32_t size);
};

#endif //!__MEMORY_H__
