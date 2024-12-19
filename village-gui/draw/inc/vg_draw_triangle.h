//###########################################################################
// vg_draw_triangle.h
// Declarations of the functions that about draw triangle
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_TRIANGLE_H__
#define __VG_DRAW_TRIANGLE_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"


/// @brief DrawTriangle
class DrawTriangle
{
private:
	//Members
	VgDevices* devices;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(DrawArea layerArea, DrawArea drawArea, int color);
};

#endif //!__VG_DRAW_TRIANGLE_H__
