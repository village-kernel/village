
//###########################################################################
// stdlib.h
// Header file for std lib
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

int atexit(void (*function)(void));
int rand(void);
void* malloc(size_t size);
void free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif // !__STD_LIB_H__
