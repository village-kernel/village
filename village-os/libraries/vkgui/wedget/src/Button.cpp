//###########################################################################
// Button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Button.h"


/// @brief Constructor
Button::Button()
	:x0(0),
	y0(0),
	text(NULL)
{
}


/// @brief Destructor
Button::~Button()
{
}


/// @brief Init content
void Button::InitContent()
{

}


/// @brief Draw content
void Button::DrawContent()
{
	if (NULL != text)
	{
		int x0 = GetLocX() + (GetWidth() / 2) - (strlen(text) * DrawingDefs::Font16 / 4);
		int y0 = GetLocY() + (GetHeight() / 2 - DrawingDefs::Font16 / 2);
		drawing->string.Set(x0, y0, text);
	}
}


/// @brief 
/// @param text 
void Button::SetText(char* text)
{
	this->text = text;
}
