//###########################################################################
// GUI.cpp
// Definitions of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "GUI.h"
#include "stdarg.h"
#include "stdio.h"
#include "Village.h"


///Constructor
GUI::GUI()
{
}


///Intialize
void GUI::Initialize(const char* driver)
{
	Driver* lcdDriver = village.GetDriverByName(driver);

	if (NULL != lcdDriver)
	{
		LcdDriver* lcd = NULL;
		lcdDriver->IOCtrl(0, (void*)&lcd);
		disp.Initialize(lcd);
	}
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
