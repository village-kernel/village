//###########################################################################
// Cursor.cpp
// Definitions of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cursor.h"


/// @brief 
Cursor::Cursor()
	:locX(0),
	locY(0)
{}


/// @brief 
void Cursor::Initialize()
{

}


/// @brief 
void Cursor::Show()
{
	display->DrawRectangle(locX, locY, locX + width, locY + height, Display::White);
	
	locX = GetLocX();
	locY = GetLocY();
	
	display->DrawRectangle(locX, locY, locX + width, locY + height);

	Wedget::Show();
}
