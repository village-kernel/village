//###########################################################################
// vg_draw_arc.h
// Declarations of the functions that about draw arc
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_ARC_H__
#define __VG_DRAW_ARC_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"


/// @brief DrawArc
class DrawArc
{
private:
	//Members
	GraphicsDevices* devices;
public:
	//Methods
	void Initiate(GraphicsDevices* devices);
	void Execute(DrawArea layerArea, DrawArea drawArea, int color);
};

#endif //!__VG_DRAW_ARC_H__
