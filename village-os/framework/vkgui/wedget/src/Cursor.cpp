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
	static uint32_t colorBits[250] = {0};
	static bool isReady = false;
	
	if (isReady)
	{
		display->DrawCircle(locX, locY, 5, colorBits);
	}
	
	locX = GetLocX();
	locY = GetLocY();
	display->ReadCircle(locX, locY, 5, colorBits);
	display->DrawCircle(locX, locY, 5);

	isReady = true;
}
