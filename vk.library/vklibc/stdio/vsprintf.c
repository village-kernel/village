//###########################################################################
// vsprintf.c
// Header file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"

/// @brief 
/// @param str 
/// @param format 
/// @param ap 
/// @return 
int vsprintf(char* buf, const char* format, va_list ap)
{
	return vsnprintf(buf, 512, format, ap);
}
