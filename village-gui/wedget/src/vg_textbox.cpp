//###########################################################################
// vg_textbox.cpp
// Definitions of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_textbox.h"


/// @brief Constructor
TextBox::TextBox()
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"textbox");
}


/// @brief Destructor
TextBox::~TextBox()
{
}


/// @brief TextBox binding text
/// @param text 
void TextBox::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief TextBox set text
/// @param text 
void TextBox::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief TextBox get text
/// @return 
char* TextBox::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief TextBox initiate
/// @param devices 
void TextBox::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	drawText.Initiate(devices);
	drawText.SetAlignment(DrawText::_AlignLeft);
}


/// @brief TextBox redraw
/// @param drawArea 
void TextBox::Redraw(DrawArea drawArea)
{
	Wedget::Redraw(drawArea);

	drawText.Execute(layerArea, drawArea, GetText());
}
