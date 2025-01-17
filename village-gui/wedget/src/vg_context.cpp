//###########################################################################
// vg_context.cpp
// Definitions of the functions that manage context
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_context.h"
#include "vk_event_codes.h"


/// @brief Constructor
VgContext::VgContext()
{
	SetTitle((char*)"context");
}


/// @brief Destructor
VgContext::~VgContext()
{
}


/// @brief Get update areas
VgDrawAreas VgContext::GetUpdateAreas()
{
	return updateAreas;
}


/// @brief Move context
/// @param input 
void VgContext::MoveContext(VgInputData input)
{
	VgDrawAreas areas;

	areas = layer.AddAreaToAreas(areas, layerArea);
	
	MoveTo(input.point.x, input.point.y);

	areas = layer.AddAreaToAreas(areas, layerArea);

	this->updateAreas = areas;
}


/// @brief Update active
/// @param active 
/// @return 
void VgContext::UpdateActive(bool active)
{
	SetHidden(!active);
	UpdateRequest(true);
}


/// @brief Set actived
/// @param active 
void VgContext::SetActived(bool active)
{
	if (!active && !IsHidden())
	{
		UpdateActive(false);
	}
	VgWedget::SetActived(active);
}


/// @brief VgContext Initiate
/// @param devices 
void VgContext::InitContent(VgDevices* devices)
{
	SetFloatable(true);
}


/// @brief VgContext Execute
/// @param input 
void VgContext::ExecContent(VgInputData input)
{
	static bool isPressed = false;
	static int lastx = 0, lasty = 0;

	if (!isPressed && VgKeyState::_Pressed == input.state)
	{
		if (EventCode::_BtnRight == input.key)
		{
			if (IsHidden() || input.point.x != lastx || input.point.y != lasty)
			{
				MoveContext(input);
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
	else if (VgKeyState::_Released == input.state)
	{
		isPressed = false;
	}
}


/// @brief VgContext draw
/// @param drawArea 
void VgContext::DrawContent(VgDrawArea drawArea)
{

}
