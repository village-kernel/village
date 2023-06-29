//###########################################################################
// GUI.cpp
// Definitions of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "GUI.h"
#include "stdarg.h"
#include "stdio.h"


///Constructor
GUI::GUI()
{
}


///Intialize
void GUI::Initialize(LcdDriver* lcd)
{
	this->disp.Initialize(lcd);
}


///Display Printf
void GUI::Printf(const char* format, ...)
{
	lock.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	disp.ShowString((uint8_t*)data);
	lock.Unlock();
}
