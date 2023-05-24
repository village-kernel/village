//###########################################################################
// printf.c
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"

/// @brief 
/// @param  
/// @param  
/// @return 
int printf(char const* format, ...)
{
	va_list ap;
	char buf[512];
	int n;

	va_start(ap, format);
	n = vsprintf(buf, format, ap);
	va_end(ap);

	puts(buf);

	return n;
}
