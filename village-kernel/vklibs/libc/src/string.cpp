//###########################################################################
// memcmp.c
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
extern "C" void* memcpy(void* dst, const void* src, size_t len)
{
    for (size_t i = 0; i < len; i++)
	{
        ((volatile uint8_t*)dst)[i] = ((volatile uint8_t*)src)[i];
    }
	return dst;
}


/// @brief memmove - move memory area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
extern "C" void* memmove(void* dst, const void* src, size_t len)
{
    for (size_t i = 0; i < len; i++)
	{
        ((volatile uint8_t*)dst)[i] = ((volatile uint8_t*)src)[i];
		((volatile uint8_t*)src)[i] = 0;
    }
	return dst;
}


/// @brief memset - fill a byte string with a byte value
/// @param b 
/// @param c 
/// @param len 
/// @return its first argument
extern "C" void* memset(void* b, int c, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		((volatile uint8_t*)b)[i] = c;
	}
	return b;
}


/// @brief memcmp
/// @param s1 
/// @param s2 
/// @param n
/// @return 0 if strings are equal
/// @return >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2.
/// @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2.
extern "C" int memcmp(const void* s1, const void* s2, size_t n)
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


/// @brief strcpy - copy memory area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
extern "C" char* strcpy(char* dst, const char* src)
{
	volatile size_t size = 0;
	
    for (size = 0; '\0' != src[size]; size++)
	{
        dst[size] = src[size];
    }

	dst[size] = '\0';

	return dst;
}


/// @brief strncpy - copy string area
/// @param dst 
/// @param src 
/// @param n 
/// @return the original value of dst
extern "C" char* strncpy(char* dst, const char* src, size_t len)
{
    for (size_t i = 0; i < len; i++)
	{
        dst[i] = src[i];
		if ('\0' == src[i]) break;
    }
	return dst;
}


/// @brief strcat
/// @param s1 
/// @param s2 
/// @return 
extern "C" char* strcat(char* s1, const char* s2)
{
	volatile size_t size1 = 0;
	volatile size_t size2 = 0;

	while(s1[size1]) { size1++; }
	while(s2[size2]) { s1[size1++] = s2[size2++]; }
	s1[size1] = '\0';

	return s1;
}


/// @brief strncat
/// @param s1 
/// @param s2 
/// @param n 
/// @return 
extern "C" char* strncat(char* s1, const char* s2, size_t n)
{
	volatile size_t size1 = 0;
	volatile size_t size2 = 0;

	while(s1[size1]) { size1++; }
	while(s2[size2]) { s1[size1++] = s2[size2++]; if (size2 >= n) break; }
	s1[size1] = '\0';

	return s1;
}



/// @brief strcmp
/// @param s1 
/// @param s2 
/// @return 0 if strings are equal
/// @return >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2.
/// @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2.
extern "C" int strcmp(const char* s1, const char* s2)
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


/// @brief strncmp
/// @param s1 
/// @param s2 
/// @param n
/// @return 0 if strings are equal
/// @return >0 if the first non-matching character in str1 is greater (in ASCII) than that of str2.
/// @return <0 if the first non-matching character in str1 is lower (in ASCII) than that of str2.
extern "C" int strncmp(const char* s1, const char* s2, size_t n)
{
	int ret = 0 ;

    while ((n--) && !(ret = (unsigned int)*s1 - (unsigned int)*s2) && *s2)
	{
        ++s1;
        ++s2;
    }

    if (ret < 0) ret = -1;
    else if (ret > 0) ret = 1;

    return ret;
}


/// @brief strlen
/// @param str
/// @return 
extern "C" size_t strlen(const char* s)
{
	volatile size_t size = 0;

    while(s[size]) size++;

    return size;
}


/// @brief strnlen
/// @param s 
/// @param maxlen 
/// @return 
extern "C" size_t strnlen(const char* s, size_t maxlen)
{
	volatile size_t size = 0;

    while(s[size] && (size != maxlen)) size++;

    return size;
}


/// @brief strchr
/// @param s 
/// @param c 
/// @return 
extern "C" char* strchr(const char* s, int c)
{
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c) return (char*)(s + i);
	}
	return NULL;
}


/// @brief 
/// @param s 
/// @param c 
/// @return 
extern "C" char* strrchr(const char* s, int c)
{
	volatile int pos = -1;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c) pos = i;
	}
	return (-1 != pos) ? (char*)(s + pos) : NULL;
}
