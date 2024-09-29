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
void Button::Setup()
{

}


/// @brief 
void Button::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	int textX = locX + (width / 2) - (strlen(text) * Display::Font16 / 4);
	int textY = locY + (height / 2 - Display::Font16 / 2);
	display->ShowString(textX, textY, (uint8_t*)text);
	display->DrawRectangle(locX, locY, locX + width, locY + height);
	Wedget::Show();
}


/// @brief 
/// @param text 
void Button::SetText(char* text)
{
	this->text = text;
}
