//###########################################################################
// vg_draw_defs.h
// Declarations of the functions that about draw defines
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_DEFS_H__
#define __VG_DRAW_DEFS_H__

#include "stdint.h"
#include "stddef.h"


/// @brief DrawArea
struct DrawArea
{
	int sx;
	int ex;
	int sy;
	int ey;

	DrawArea
	(
		int sx = 0,
		int ex = 0,
		int sy = 0,
		int ey = 0
	):
		sx(sx),
		ex(ex),
		sy(sy),
		ey(ey)
	{}
};


/// @brief DrawData
struct DrawData
{
	DrawArea   area;
	void*      pixels;

	DrawData()
		:pixels(NULL)
	{}
};


/// @brief DrawDefs
class DrawDefs
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

	//DrawMode
	enum DrawMode
	{
		Multiply    = 0,
		NotMultiply = 1,
	};

	//Static constants
	static const int defBgColor = Color16::White;
	static const int defStrokeColor = Color16::Black;
};

#endif //!__VG_DRAW_DEFS_H__
