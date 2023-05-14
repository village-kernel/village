//###########################################################################
// string.c
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdint.h"


/// @brief memcpy - copy memory area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
void* memcpy(void* dst, const void* src, size_t n)
{
    for (int i = 0; i < n; i++)
	{
        ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
    }
	return dst;
}


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


/// @brief 
/// @param s1 
/// @param s2 
/// @return 
char* strcat(char* s1, const char* s2)
{
	return s1;
}


/// @brief 
/// @param s1 
/// @param s2 
/// @param n 
/// @return 
char* strncat(char* s1, const char* s2, size_t n)
{
	return s1;
}


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


/// @brief 
/// @param str
/// @return 
size_t strlen(const char* str)
{
	size_t size = 0;

    while(str[size]) size++;

    return size;
}
