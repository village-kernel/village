//###########################################################################
// vg_lcddev.h
// Declarations of the functions that manage dispaly
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LCD_DEV_H__
#define __VG_LCD_DEV_H__

#include "stddef.h"
#include "stdint.h"
#include "vg_draw_defs.h"


/// @brief Lcddev
class Lcddev
{
public:
	//Methods
	virtual void Setup() = 0;
	virtual void Exit() = 0;

	//Draw methods
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void Point(int x, int y, int color) = 0;
	virtual void Flush(DrawArea area, void* pixels) = 0;
};

#endif //!__VG_LCD_DEV_H__
