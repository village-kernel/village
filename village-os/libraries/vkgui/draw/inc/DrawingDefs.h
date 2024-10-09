//###########################################################################
// Drawing.h
// Declarations of the functions that about drawing defines
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_DEFS_H__
#define __DRAWING_DEFS_H__

#include "stdint.h"
#include "stddef.h"


/// @brief Drawing
class DrawingDefs
{
public:
	//Color16
	enum Color16
	{
		White      = 0xFFFF,
		Black      = 0x0000,
		Blue       = 0x001F,
		Bred       = 0XF81F,
		Gred       = 0XFFE0,
		Gblue      = 0X07FF,
		Red        = 0xF800,
		Magenta    = 0xF81F,
		Green      = 0x07E0,
		Cyan       = 0x7FFF,
		Yellow     = 0xFFE0,
		Brown      = 0XBC40,
		Brred      = 0XFC07,
		Gray       = 0X8430,
		Darkblue   = 0X01CF,
		Lightblue  = 0X7D7C,
		Grayblue   = 0X5458,
		Lightgreen = 0X841F,
		Lgray      = 0XC618,
		Lgrayblue  = 0XA651,
		Lbblue     = 0X2B12,
	};

	//FontSize
	enum FontSize
	{
		Font16 = 16,
		Font24 = 24,
	};

	//DrawingMode
	enum DrawingMode
	{
		Multiply    = 0,
		NotMultiply = 1,
	};

	//Static constants
	static const int defBgColor = Color16::White;
	static const int defStrokeColor = Color16::Black;
};

#endif //!__DRAWING_DEFS_H__
