//###########################################################################
// vg_draw_mask.h
// Declarations of the functions that about draw mask
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_MASK_H__
#define __VG_DRAW_MASK_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"
#include "vg_draw_line.h"


/// @brief DrawMask
class DrawMask
{
private:
	//Members
	GraphicsDevices* devices;
	DrawLine line;
public:
	//Methods
	void Initiate(GraphicsDevices* devices);
	void Execute(DrawArea layerArea, DrawArea drawArea, int color);
};

#endif //!__VG_DRAW_MASK_H__
