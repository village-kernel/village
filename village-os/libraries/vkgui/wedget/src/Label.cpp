//###########################################################################
// Label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Label.h"


/// @brief 
/// @param text 
void Label::SetText(char* text)
{
	this->label = text;
}


/// @brief 
void Label::DrawContent()
{
	if (NULL != label)
	{
		int locX = GetLocX();
		int locY = GetLocY();
		drawing->string.Set(locX, locY, label);
	}
}
