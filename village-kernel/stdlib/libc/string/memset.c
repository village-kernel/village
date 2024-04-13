//###########################################################################
// memset.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief memset - fill a byte string with a byte value
/// @param b 
/// @param c 
/// @param len 
/// @return its first argument
void* memset(void* b, int c, size_t len)
{
    uint8_t *temp = (uint8_t *)b;
    for ( ; len != 0; len--) *temp++ = c;
	return b;
}
