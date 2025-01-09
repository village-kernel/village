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


/// @brief VgDrawRect
class VgDrawRect
{
private:
	//Members
	VgDevices* devices;

	//Members
	VgMath math;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, int color);
	void Execute(VgDrawArea layerArea, VgDrawAreas drawAreas, int color);
};

#endif //!__VG_DRAW_RECT_H__
