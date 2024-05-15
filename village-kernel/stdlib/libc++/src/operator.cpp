//###########################################################################
// operator.cpp
// Definitions of the functions that memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdint.h"
#include "stddef.h"
#include "kernel.h"


/// @brief Override new
/// @param size byte size
/// @return address
void *operator new(size_t size)
{
	return (void*)kernel->memory.HeapAlloc((uint32_t)size);
}


/// @brief Override new[]
/// @param size byte size
/// @return address
void *operator new[](size_t size)
{
	return (void*)kernel->memory.HeapAlloc((uint32_t)size);
}


/// @brief Override delete
/// @param ptr address
void operator delete(void *ptr)
{
	kernel->memory.Free((uint32_t)ptr);
}


/// @brief Override delete[]
/// @param ptr address
void operator delete[](void *ptr)
{
	kernel->memory.Free((uint32_t)ptr);
}


/// @brief Override delete
/// @param ptr address
/// @param size byte size
void operator delete(void *ptr, size_t size)
{
	kernel->memory.Free((uint32_t)ptr, size);
}


/// @brief Override delete[]
/// @param ptr address
/// @param size byte size
void operator delete[](void *ptr, size_t size)
{
	kernel->memory.Free((uint32_t)ptr, size);
}
