//###########################################################################
// strnlen.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief 
/// @param s 
/// @param maxlen 
/// @return 
size_t strnlen(const char* s, size_t maxlen)
{
	size_t size = 0;

    while(s[size] && (size != maxlen)) size++;

    return size;
}
