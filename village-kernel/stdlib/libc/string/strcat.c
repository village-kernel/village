//###########################################################################
// strcat.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief 
/// @param s1 
/// @param s2 
/// @return 
char* strcat(char* s1, const char* s2)
{
	size_t size1 = 0;
	size_t size2 = 0;

	while(s1[size1]) { size1++; }
	while(s2[size2]) { s1[size1++] = s2[size2++]; }
	s1[size1] = '\0';

	return s1;
}
