//###########################################################################
// memmove.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief memmove - move memory area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
void* memmove(void* dst, const void* src, size_t len)
{
    for (int i = 0; i < len; i++)
	{
        ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
		((uint8_t*)src)[i] = 0;
    }
	return dst;
}
