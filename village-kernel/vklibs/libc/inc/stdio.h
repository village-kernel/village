//###########################################################################
// stdio.h
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "stdarg.h"

int putchar(int c);
int puts(const char* str);

int printf(char const* format, ...);
int sprintf(char* str, const char* format, ...);
int snprintf(char* str, size_t size, const char* format, ...);
int asprintf(char** ret, const char* format, ...);
int dprintf(int fd, const char* format, ...);

int vprintf(const char* format, va_list ap);
int vsprintf(char* str, const char* format, va_list ap);
int vsnprintf(char* str, size_t size, const char* format, va_list ap);
int vasprintf(char** ret, const char* format, va_list ap);
int vdprintf(int fd, const char* format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif // !__STDIO_H__
