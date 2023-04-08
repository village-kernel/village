//###########################################################################
// GUI.cpp
// Definitions of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "GUI.h"

///Constructor
GUI::GUI()
{
}


///Intialize
void GUI::Initialize(LcdDriver* lcd)
{
	this->disp.Initialize(lcd);
}
