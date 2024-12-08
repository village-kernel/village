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


/// @brief Wedget Execute
/// @param input 
void Button::Execute(IndevData input)
{
	if (layer.IsCoordinateInArea(input.point.x, input.point.y, layerArea))
	{
		if (KeyState::_Pressed == input.state)
		{
			if (NULL != cmd) cmd->Execute();
		}
	}
}
