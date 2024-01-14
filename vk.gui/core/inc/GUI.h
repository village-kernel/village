//###########################################################################
// GUI.h
// Declarations of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GUI_H__
#define __GUI_H__

#include "Display.h"
#include "Wedgets.h"

///GUI
class GUI
{
private:
	//Members
	LcdDriver*  lcdDriver;
	Display*    display;
	Wedget*     mainwin;
public:
	//Methods
	GUI();
	~GUI();
	void Initialize(const char* drvname);
	Wedget* CreateMainWindow();
};

#endif //!__GUI_H__
