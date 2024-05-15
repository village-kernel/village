//###########################################################################
// StackFrame.cpp
// Definitions of the functions that manage stack frame
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Frame.h"

/// @brief 
Frame::Frame()
{
}


/// @brief Setup
void Frame::Setup()
{
}


/// @brief Show
void Frame::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	//"□"
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	//"-"
	display->DrawLine(locX, locY + 20, locX + width, locY + 20);
	//"|"	
	display->DrawLine(locX + width - 60, locY, locX + width - 60, locY + 20);
	display->DrawLine(locX + width - 40, locY, locX + width - 40, locY + 20);
	display->DrawLine(locX + width - 20, locY, locX + width - 20, locY + 20);
	//"-"
	display->DrawLine(locX + width - 55, locY + 10, locX + width - 45, locY + 10);
	//"□"
	display->DrawRectangle(locX + width - 35, locY + 5, locX + width - 25, locY + 15);
	//"x"
	display->DrawLine(locX + width - 15, locY + 5, locX + width - 5, locY + 15);
	display->DrawLine(locX + width - 15, locY + 15, locX + width - 5, locY + 5);
	
	Wedget::Show();
}
