//###########################################################################
// Label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Label.h"


/// @brief Constructor
Label::Label()
	:label(NULL)
{
}


/// @brief Destructor
Label::~Label()
{
}


/// @brief Init content
void Label::InitContent()
{

}


/// @brief Draw content
void Label::DrawContent()
{
	if (NULL != label)
	{
		int locX = GetLocX();
		int locY = GetLocY();
		drawing->string.Set(locX, locY, label);
	}
}


/// @brief 
/// @param text 
void Label::SetText(char* text)
{
	this->label = text;
}
