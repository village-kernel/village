
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

int atexit(void (*function)(void));
int rand(void);

#ifdef __cplusplus
}
#endif

#endif // !__STD_LIB_H__
