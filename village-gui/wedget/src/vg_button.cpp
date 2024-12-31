//###########################################################################
// vg_button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_button.h"
#include "vk_event_codes.h"


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
	static bool isPressed = false;

	if (layer.IsCoordinateInArea(input.point.x, input.point.y, layerArea))
	{
		if (EventCode::_BtnLeft == input.key)
		{
			if (!isPressed && KeyState::_Pressed == input.state)
			{
				isPressed = true; if (NULL != cmd) cmd->Execute();
			}
			else if (KeyState::_Released == input.state)
			{
				isPressed = false;
			}
		}
	}
}
