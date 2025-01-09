//###########################################################################
// vg_textbox.cpp
// Definitions of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_textbox.h"


/// @brief Constructor
VgTextBox::VgTextBox()
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"textbox");
}


/// @brief Destructor
VgTextBox::~VgTextBox()
{
}


/// @brief VgTextBox binding text
/// @param text 
void VgTextBox::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief VgTextBox set text
/// @param text 
void VgTextBox::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief VgTextBox get text
/// @return 
char* VgTextBox::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief VgTextBox initiate
/// @param devices 
void VgTextBox::InitContent(VgDevices* devices)
{
	drawText.Initiate(devices);
	drawText.SetAlignment(VgDrawText::_AlignLeft);
}


/// @brief VgTextBox execute
/// @param input 
void VgTextBox::ExecContent(VgInputData input)
{

}


/// @brief VgTextBox draw
/// @param drawArea 
void VgTextBox::DrawContent(VgDrawArea drawArea)
{
	drawText.Execute(layerArea, drawArea, GetText());
}
