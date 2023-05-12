//###########################################################################
// string.h
// Header file for string classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STRING_H__
#define __STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

char* strcat(char* s1, const char* s2);
char* strncat(char* s1, const char* s2, size_t n);
int strcmp(const char* s1, const char* s2);
size_t strlen(const char* s1);

#ifdef __cplusplus
}
#endif

#endif // !__STRING_H__
