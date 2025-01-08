//###########################################################################
// vg_textbox.h
// Declarations of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TEXT_BOX_H__
#define __VG_TEXT_BOX_H__

#include "vg_wedget.h"
#include "vg_draw_text.h"
#include "vg_input_data.h"


/// @brief TextBox
class TextBox : public Wedget
{
private:
	//Memebers
	char* 	      text;
	IData<char*>* bText;

	//Members
	DrawText      drawText;
public:
	//Methods
	TextBox();
	~TextBox();

	//Attribute Methods
	void BindingText(IData<char*>* text);
	void SetText(char* text);
	char* GetText();

	//Methods
	void Initiate(VgDevices* devices);
	void Redraw(DrawArea drawArea);
};

#endif //!__VG_TEXT_BOX_H__
