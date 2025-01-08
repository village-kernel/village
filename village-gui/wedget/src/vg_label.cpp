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
	SetMultiply(true);
}


/// @brief Destructor
Label::~Label()
{
}


/// @brief Label set text
/// @param text 
void Label::SetText(char* text)
{
	this->label = text;
}


/// @brief Label initiate
/// @param devices 
void Label::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	drawlab.Initiate(devices);
	drawlab.SetAlignment(DrawText::_AlignCenter);
}


/// @brief Label redraw
/// @param drawArea 
void Label::Redraw(DrawArea drawArea)
{
	drawlab.Execute(layerArea, drawArea, label);
}
