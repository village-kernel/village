//###########################################################################
// vg_button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_button.h"


/// @brief Constructor
Button::Button()
	:text(NULL)
{
}


/// @brief Destructor
Button::~Button()
{
}


/// @brief 
/// @param text 
void Button::SetText(char* text)
{
	this->text = text;
}
