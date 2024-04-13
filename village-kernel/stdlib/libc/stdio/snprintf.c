//###########################################################################
// snprintf.c
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"

/// @brief 
/// @param str 
/// @param size 
/// @param format 
/// @param  
/// @return 
int snprintf(char* str, size_t size, const char* format, ...)
{
	va_list ap;
	int n;

	va_start(ap, format);
	n = vsnprintf(str, size, format, ap);
	va_end(ap);
	return n;
}
