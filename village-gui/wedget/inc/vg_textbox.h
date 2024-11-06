//###########################################################################
// vg_textbox.h
// Declarations of the functions that manage text box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TEXT_BOX_H__
#define __VG_TEXT_BOX_H__

#include "vg_wedget.h"
#include "vg_scrollbar.h"


/// @brief TextBox
class TextBox : public Wedget
{
public:
	//Methods
	TextBox();
	~TextBox();
	
	void InitContent();
	void DrawContent();
};

#endif //!__VG_TEXT_BOX_H__
