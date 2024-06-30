//###########################################################################
// string.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdlib.h"
#include "ctype.h"
#include "Kernel.h"


/// @brief atexit
/// @param function 
/// @return 
extern "C" int atexit(void (*function)(void))
{
	return 0;
}


/// @brief malloc
/// @param size 
/// @return 
extern "C" void* malloc(size_t size)
{
	return (void*)kernel->memory.HeapAlloc((uint32_t)size);
}



/// @brief free
/// @param ptr 
extern "C" void free(void* ptr)
{
	kernel->memory.Free((uint32_t)ptr);
}


/// @brief rand
/// @param  
/// @return 
extern "C" int rand(void)
{
	return kernel->system.GetSysClkCounts();
}


/// @brief abs
/// @param i 
/// @return 
extern "C" int abs(int i)
{
	if (i < 0) i = -i;
	return i;
}


/// @brief labs
/// @param i 
/// @return 
extern "C" long labs(long i)
{
	if (i < 0) i = -i;
	return i;
}


/// @brief atoi
/// @param str 
/// @return 
extern "C" int atoi(const char *str)
{
	int i = 0;

	while (isdigit(*str))
	{
		i = i * 10 + *(str++) - '0';
	}

	return i;
}
