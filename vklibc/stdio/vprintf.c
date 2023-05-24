//###########################################################################
// vprintf.c
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"

/// @brief 
/// @param format 
/// @param ap 
/// @return 
int vprintf(const char* format, va_list ap)
{
	char buf[512];
	int n = vsprintf(buf, format, ap);
	puts(buf);
	return n;
}
