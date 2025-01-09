//###########################################################################
// vg_label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_label.h"


/// @brief Constructor
VgLabel::VgLabel()
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"label");
	SetMultiply(true);
}


/// @brief Destructor
VgLabel::~VgLabel()
{
}


/// @brief VgLabel binding text
/// @param bText 
void VgLabel::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief VgLabel set text
/// @param text 
void VgLabel::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief VgLabel get text
/// @return 
char* VgLabel::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief VgLabel redraw background
/// @param areas 
void VgLabel::RedrawBackgroundAreas(VgDrawAreas areas)
{

}


/// @brief VgLabel initiate
/// @param devices 
void VgLabel::InitContent(VgDevices* devices)
{
	drawText.Initiate(devices);
	drawText.SetAlignment(VgDrawText::_AlignCenter);
}


/// @brief VgLabel execute
/// @param input 
void VgLabel::ExecContent(VgInputData input)
{

}


/// @brief VgLabel draw
/// @param drawArea 
void VgLabel::DrawContent(VgDrawArea drawArea)
{
	drawText.Execute(layerArea, drawArea, GetText());
}
