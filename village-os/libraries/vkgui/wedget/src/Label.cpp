//###########################################################################
// Label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Label.h"


/// @brief 
void Label::DrawContent()
{
	int locX = GetLocX();
	int locY = GetLocY();
	drawing->string.Set(locX, locY, label);
}


/// @brief 
/// @param text 
void Label::SetText(char* text)
{
	this->label = text;
}
