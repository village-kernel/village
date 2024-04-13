//###########################################################################
// strncpy.c
// Sources file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief strncpy - copy string area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
char* strncpy(char* dst, const char* src, size_t len)
{
    for (int i = 0; i < len; i++)
	{
        dst[i] = src[i];
		if ('\0' == src[i]) break;
    }
	return dst;
}
