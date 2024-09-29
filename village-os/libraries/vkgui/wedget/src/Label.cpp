//###########################################################################
// Label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Label.h"


/// @brief 
void Label::Setup()
{

}


/// @brief 
void Label::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->ShowString(locX, locY, (uint8_t*)label);
	Wedget::Show();
}


/// @brief 
/// @param label 
void Label::SetLabel(char* label)
{
	this->label = label;
}
