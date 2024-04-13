//###########################################################################
// strcmp.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief strcmp
/// @param s1 
/// @param s2 
/// @return 0 if strings are equal
/// @return >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2.
/// @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2.
int strcmp(const char* s1, const char* s2)
{
	int ret = 0 ;

	while (!(ret = (unsigned int)*s1 - (unsigned int)*s2) && *s2)
	{
		++s1;
		++s2;
	}

	if (ret < 0) ret = -1;
	else if (ret > 0) ret = 1;

	return ret;
}
