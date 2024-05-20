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

void* memcpy(void* dst, const void* src, size_t len);
void* memmove(void* dst, const void* src, size_t len);
void* memset(void* b, int c, size_t len);
int memcmp(const void* s1, const void* s2, size_t n);

char* strcpy(char* dst, const char* src);
char* strncpy(char* dst, const char* src, size_t len);
char* strcat(char* s1, const char* s2);
char* strncat(char* s1, const char* s2, size_t n);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
size_t strlen(const char* s);
size_t strnlen(const char* s, size_t maxlen);
char* strchr(const char *s, int c);
char* strrchr(const char *s, int c);

#ifdef __cplusplus
}
#endif

#endif // !__STRING_H__
