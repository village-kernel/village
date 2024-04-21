//###########################################################################
// strchr.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief strchr
/// @param s 
/// @param c 
/// @return 
char* strchr(const char* s, int c)
{
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c) return (char*)(s + i);
	}
	return NULL;
}
