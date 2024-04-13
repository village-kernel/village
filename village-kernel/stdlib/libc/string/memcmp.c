//###########################################################################
// memcmp.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"

/// @brief memcmp
/// @param s1 
/// @param s2 
/// @param n
/// @return 0 if strings are equal
/// @return >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2.
/// @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2.
int memcmp(const void* s1, const void* s2, size_t n)
{
	int ret = 0 ;
	char* _s1 = (char*)s1;
	char* _s2 = (char*)s2;

	while ((n--) && !(ret = (unsigned int)*(unsigned int*)_s1 - (unsigned int)*_s2) && *_s2)
	{
		++_s1;
		++_s2;
	}

	if (ret < 0) ret = -1;
	else if (ret > 0) ret = 1;

	return ret;
}
