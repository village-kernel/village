//###########################################################################
// Button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Button.h"


/// @brief 
Button::Button()
	:text(NULL)
{
}


/// @brief 
Button::~Button()
{
}


/// @brief 
void Button::Initialize()
{

}


/// @brief 
void Button::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->ShowString(locX, locY, (uint8_t*)text);
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	Wedget::Show();
}


/// @brief 
/// @param text 
void Button::SetText(char* text)
{
	this->text = text;
}
