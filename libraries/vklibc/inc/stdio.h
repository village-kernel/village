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

#include "stdarg.h"

int vsprintf(char* str, const char* format, va_list ap);
int printf(char const*, ...);

#ifdef __cplusplus
}
#endif

#endif // !__STDIO_H__
