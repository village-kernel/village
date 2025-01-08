//###########################################################################
// vg_label.cpp
// Definitions of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_label.h"


/// @brief Constructor
Label::Label()
	:text(NULL),
	bText(NULL)
{
	SetTitle((char*)"label");
	SetMultiply(true);
}


/// @brief Destructor
Label::~Label()
{
}


/// @brief 
/// @param bText 
void Label::BindingText(IData<char*>* text)
{
	bText = text; if (bText) bText->Binding(this);
}


/// @brief Label set text
/// @param text 
void Label::SetText(char* text)
{
	this->text = text; if (bText) bText->Set(text);
}


/// @brief Label get text
/// @return 
char* Label::GetText()
{
	return bText ? bText->Get() : text;
}


/// @brief Label initiate
/// @param devices 
void Label::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	drawText.Initiate(devices);
	drawText.SetAlignment(DrawText::_AlignCenter);
}


/// @brief Label redraw
/// @param drawArea 
void Label::Redraw(DrawArea drawArea)
{
	drawText.Execute(layerArea, drawArea, GetText());
}
