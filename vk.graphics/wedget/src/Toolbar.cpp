//###########################################################################
// Toolbar.cpp
// Definitions of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Toolbar.h"


/// @brief 
void Toolbar::Initialize()
{

}


/// @brief 
void Toolbar::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	Wedget::Show();
}
