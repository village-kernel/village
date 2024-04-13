//###########################################################################
// strlen.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief 
/// @param str
/// @return 
size_t strlen(const char* s)
{
	size_t size = 0;

    while(s[size]) size++;

    return size;
}

