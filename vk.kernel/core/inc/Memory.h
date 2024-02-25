//###########################################################################
// Memory.h
// Declarations of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Module.h"


/// @brief Memory
class Memory : public Module
{
public:
	//Methods
	virtual uint32_t HeapAlloc(uint32_t size) = 0;
	virtual uint32_t StackAlloc(uint32_t size) = 0;
	virtual void Free(uint32_t memory, uint32_t size = 0) = 0;
	virtual uint32_t GetSize() = 0;
	virtual uint32_t GetUsed() = 0;
};

#endif //!__MEMORY_H__
