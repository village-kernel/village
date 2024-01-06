//###########################################################################
// strcpy.c
// Sources file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief strcpy - copy memory area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
char* strcpy(char* dst, const char* src)
{
    for (int i = 0; ;i++)
	{
        dst[i] = src[i];
		if ('\0' == src[i]) break;
    }
	return dst;
}
