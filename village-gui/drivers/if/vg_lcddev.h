//###########################################################################
// vg_lcddev.h
// Declarations of the functions that manage dispaly
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LCD_DEV_H__
#define __VG_LCD_DEV_H__

#include "vg_data.h"


/// @brief Lcddev
class Lcddev
{
public:
	//Methods
	virtual void Setup() = 0;
	virtual void Exit() = 0;

	//Draw methods
	virtual void Flush(DrawArea area, uint8_t* pixels) = 0;
};

#endif //!__VG_LCD_DEV_H__
