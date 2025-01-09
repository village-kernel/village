//###########################################################################
// vg_label.h
// Declarations of the functions that manage label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LABEL_H__
#define __VG_LABEL_H__

#include "vg_wedget.h"
#include "vg_draw_text.h"


/// @brief VgLabel
class VgLabel : public VgWedget
{
private:
	//Memebers
	char* 	      text;
	IData<char*>* bText;

	//Members
	VgDrawText      drawText;
public:
	//Methods
	VgLabel();
	~VgLabel();

	//Attribute Methods
	void BindingText(IData<char*>* text);
	void SetText(char* text);
	char* GetText();

	//Area Methods
	void RedrawBackgroundAreas(VgDrawAreas areas);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_LABEL_H__
