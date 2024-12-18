//###########################################################################
// vg_draw_rect.h
// Declarations of the functions that about draw rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_RECT_H__
#define __VG_DRAW_RECT_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"
#include "vg_math.h"


/// @brief DrawRect
class DrawRect
{
private:
	//Members
	VgDevices* devices;

	//Members
	Math math;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(DrawArea layerArea, DrawArea drawArea, int color);
};

#endif //!__VG_DRAW_RECT_H__
