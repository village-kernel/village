//###########################################################################
// vg_label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_label.h"


/// @brief Constructor
Label::Label()
	:label(NULL)
{
	SetTitle((char*)"label");
}


/// @brief Destructor
Label::~Label()
{
}


/// @brief 
/// @param text 
void Label::SetText(char* text)
{
	this->label = text;
}
