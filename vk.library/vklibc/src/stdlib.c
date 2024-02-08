//###########################################################################
// string.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdlib.h"


int atexit(void (*function)(void))
{
	return 0;
}


__attribute__((weak)) void* malloc(size_t size)
{
	return 0;
}


__attribute__((weak)) void free(void* ptr)
{
	
}


__attribute__((weak)) int rand(void)
{
	return 0;
}


__attribute__((weak)) int abs(int i)
{
	if (i < 0) i = -i;
	return i;
}


__attribute__((weak)) long labs(long i)
{
	if (i < 0) i = -i;
	return i;
}
