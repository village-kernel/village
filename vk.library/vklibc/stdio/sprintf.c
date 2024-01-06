//###########################################################################
// sprintf.c
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"

/// @brief 
/// @param str 
/// @param format 
/// @param  
/// @return 
int sprintf(char* str, const char* format, ...)
{
	va_list ap;
	int n;

	va_start(ap, format);
	n = vsprintf(str, format, ap);
	va_end(ap);
	return n;
}
