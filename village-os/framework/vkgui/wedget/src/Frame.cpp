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
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	display->DrawRectangle(locX, locY, locX + width, locY + 20);
	display->DrawRectangle(locX + width - 60, locY, locX + width - 40, locY + 20);
	display->DrawRectangle(locX + width - 40, locY, locX + width - 20, locY + 20);
	display->DrawRectangle(locX + width - 20, locY, locX + width - 0,  locY + 20);
	Wedget::Show();
}
