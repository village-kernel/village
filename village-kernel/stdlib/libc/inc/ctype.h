//###########################################################################
// stdint.h
// Header file for stdint classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CTYPE_H__
#define __CTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

static inline int isdigit(int ch)
{
	return (ch >= '0') && (ch <= '9');
}

static inline int isxdigit(int ch)
{
	if (isdigit(ch))
		return true;

	if ((ch >= 'a') && (ch <= 'f'))
		return true;

	return (ch >= 'A') && (ch <= 'F');
}

#ifdef __cplusplus
}
#endif

#endif //!__CTYPE_H__
