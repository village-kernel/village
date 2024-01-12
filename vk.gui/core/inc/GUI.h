//###########################################################################
// GUI.h
// Declarations of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GUI_H__
#define __GUI_H__

#include "Display.h"
#include "Mutex.h"

///GUI
class GUI
{
private:
	//Static constants
	static const uint16_t buf_size = 100;

	//Members
	Mutex   lock;
	char    data[buf_size];
	Display disp;
public:
	//Methods
	GUI();
	void Initialize(const char* driver);
	void Printf(const char* format, ...);
};

#endif //!__GUI_H__
