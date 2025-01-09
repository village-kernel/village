//###########################################################################
// vg_draw_text.h
// Declarations of the functions that about draw text
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_TEXT_H__
#define __VG_DRAW_TEXT_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"
#include "vg_math.h"


/// @brief VgDrawText
class VgDrawText
{
public:
	//Alignment
	enum Alignment
	{
		_AlignRight,
		_AlignLeft,
		_AlignCenter,
	};
private:
	//Members
	VgDevices* devices;

	//Members
	VgMath math;

	//Members
	int fontSize;
	int fontWidth;
	int fontHeight;
	int fontColor;
	Alignment alignment;

	//Methods
	int GetFontIndex(int chr);
	int GetFontMatrix(int index, int row);
public:
	//Methods
	VgDrawText();
	~VgDrawText();

	//Methods
	void SetFontSize(int font);
	void SetFontColor(int color);
	void SetAlignment(Alignment align);

	//Methods
	void Initiate(VgDevices* devices);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, char  chr);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, char* str);
};

#endif //!__VG_DRAW_TEXT_H__
