//###########################################################################
// Button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Button.h"


/// @brief 
Button::Button()
	:x0(0),
	y0(0),
	text(NULL)
{
}


/// @brief 
Button::~Button()
{
}


/// @brief 
/// @param text 
void Button::SetText(char* text)
{
	this->text = text;
}


/// @brief 
void Button::InitContent()
{
	x0 = GetLocX() + (GetWidth() / 2) - (strlen(text) * DrawingDefs::Font16 / 4);
	y0 = GetLocY() + (GetHeight() / 2 - DrawingDefs::Font16 / 2);
}


/// @brief 
void Button::DrawContent()
{
	drawing->string.Set(x0, y0, text);
}
