//###########################################################################
// vg_context.cpp
// Definitions of the functions that manage context
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_context.h"
#include "vk_event_codes.h"


/// @brief Constructor
Context::Context()
{
}


/// @brief Destructor
Context::~Context()
{
}


/// @brief Get update areas
DrawAreas Context::GetUpdateAreas()
{
	DrawAreas areas;

	if (!layer.IsAreaSame(oldArea, layerArea))
	{
		areas.Add(oldArea);
	}

	areas.Append(Wedget::GetUpdateAreas());

	return areas;
}


/// @brief Update active
/// @param active 
/// @return 
void Context::UpdateActive(bool active)
{
	SetHidden(!active);
	UpdateRequest(true);
}


/// @brief Set focus
/// @param focus 
void Context::SetFocus(bool focus)
{
	if (!focus && !IsHidden())
	{
		UpdateActive(false);
	}
	Wedget::SetFocus(focus);
}


/// @brief Context Initiate
/// @param devices 
void Context::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	SetFloatable(true);
}


/// @brief Context menu is active
/// @param input 
void Context::Execute(IndevData input)
{
	static bool isPressed = false;
	static int lastx = 0, lasty = 0;

	if (!isPressed && KeyState::_Pressed == input.state)
	{
		if (EventCode::_BtnRight == input.key)
		{
			if (IsHidden() || input.point.x != lastx || input.point.y != lasty)
			{
				oldArea = layerArea;
				MoveTo(input.point.x, input.point.y);
				lastx = input.point.x;
				lasty = input.point.y;
				UpdateActive(true);
			}
			else
			{
				UpdateActive(false);
			}
		}
		else if (EventCode::_BtnLeft == input.key)
		{
			if (!IsHidden()) UpdateActive(false);
		}

		isPressed = true;
	}
	else if (KeyState::_Released == input.state)
	{
		isPressed = false;
	}

	Wedget::Execute(input);
}
