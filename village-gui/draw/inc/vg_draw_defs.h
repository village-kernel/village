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
#include "vg_list.h"


/// @brief DrawPoint
struct DrawPoint
{
	int x;
	int y;

	DrawPoint
	(
		int x = 0,
		int y = 0
	):
		x(x),
		y(y)
	{}
};


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


/// @brief DrawPath
typedef VgList<DrawPoint> DrawPath;


/// @brief DrawCanvas
typedef VgList<DrawPath>  DrawCanvas;


/// @brief DrawAreas
typedef VgList<DrawArea>  DrawAreas;


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
		_Black      = 0x0000,
		_Blue       = 0x001F,
		_Bred       = 0XF81F,
		_Gred       = 0XFFE0,
		_Gblue      = 0X07FF,
		_Red        = 0xF800,
		_Magenta    = 0xF81F,
		_Green      = 0x07E0,
		_Cyan       = 0x7FFF,
		_Yellow     = 0xFFE0,
		_Brown      = 0XBC40,
		_Brred      = 0XFC07,
		_Gray       = 0X8430,
		_Darkblue   = 0X01CF,
		_Lightblue  = 0X7D7C,
		_Grayblue   = 0X5458,
		_Lightgreen = 0X841F,
		_Lgray      = 0XC618,
		_Lgrayblue  = 0XA651,
		_Lbblue     = 0X2B12,
		_White      = 0xFFFF,
	};

	//FontSize
	enum FontSize
	{
		_Font16 = 16,
		_Font24 = 24,
	};

	//DrawMode
	enum DrawMode
	{
		_Multiply    = 0,
		_NotMultiply = 1,
	};

	//Static constants
	static const int defBgColor = _White;
	static const int defStrokeColor = _Black;
};

#endif //!__VG_DRAW_DEFS_H__
