//###########################################################################
// strrchr.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief 
/// @param s 
/// @param c 
/// @return 
char* strrchr(const char* s, int c)
{
	int pos = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c) pos = i;
	}
	return pos ? (char*)(s + pos) : NULL;
}
