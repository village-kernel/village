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


/// @brief VgTextBox
class VgTextBox : public VgWedget
{
private:
	//Memebers
	char* 	      text;
	IData<char*>* bText;

	//Members
	VgDrawText    drawText;
public:
	//Methods
	VgTextBox();
	~VgTextBox();

	//Attribute Methods
	void BindingText(IData<char*>* text);
	void SetText(char* text);
	char* GetText();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TEXT_BOX_H__
