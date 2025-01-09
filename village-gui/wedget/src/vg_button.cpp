//###########################################################################
// vg_button.cpp
// Definitions of the functions that manage button
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_button.h"
#include "vk_event_codes.h"


/// @brief Constructor
VgButton::VgButton()
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"button");
}


/// @brief Destructor
VgButton::~VgButton()
{
}


/// @brief VgButton binding text
/// @param text 
void VgButton::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief VgButton set text
/// @param text 
void VgButton::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief VgButton get text
/// @return 
char* VgButton::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief VgButton initiate
/// @param devices 
void VgButton::InitContent(VgDevices* devices)
{
	drawText.Initiate(devices);
	drawText.SetAlignment(VgDrawText::_AlignCenter);
}


/// @brief VgButton execute
/// @param input 
void VgButton::ExecContent(VgInputData input)
{
	if (IsInLayerArea(input.point.x, input.point.y))
	{
		ExecuteCommand(input);
	}
}


/// @brief VgButton draw
/// @param drawArea 
void VgButton::DrawContent(VgDrawArea drawArea)
{
	drawText.Execute(layerArea, drawArea, GetText());
}
