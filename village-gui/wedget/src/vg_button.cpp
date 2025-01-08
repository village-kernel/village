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
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"button");
}


/// @brief Destructor
Button::~Button()
{
}


/// @brief Button binding text
/// @param text 
void Button::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief Button set text
/// @param text 
void Button::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief Button get text
/// @return 
char* Button::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief Button initiate
/// @param devices 
void Button::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	drawText.Initiate(devices);
	drawText.SetAlignment(DrawText::_AlignCenter);
}


/// @brief Button execute
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


/// @brief Label redraw
/// @param drawArea 
void Button::Redraw(DrawArea drawArea)
{
	Wedget::Redraw(drawArea);

	drawText.Execute(layerArea, drawArea, GetText());
}
