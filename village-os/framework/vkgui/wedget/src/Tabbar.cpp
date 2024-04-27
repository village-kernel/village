//###########################################################################
// Tabbar.cpp
// Definitions of the functions that manage tab bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Tabbar.h"


/// @brief 
void Tabbar::Setup()
{

}


/// @brief 
void Tabbar::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	Wedget::Show();
}
