//###########################################################################
// GUI.h
// Declarations of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GUI_H__
#define __GUI_H__

#include "Display.h"

///GUI
class GUI
{
public:
	//Members
	Display disp;

	//Methods
	GUI();
	void Initialize(LcdDriver* lcd);
};

#endif //!__GUI_H__
