//###########################################################################
// vg_draw_label.h
// Declarations of the functions that about draw label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_LABEL_H__
#define __VG_DRAW_LABEL_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"


/// @brief DrawLabel
class DrawLabel
{
private:
	//Members
	GraphicsDevices* devices;
public:
	//Methods
	void Initiate(GraphicsDevices* devices);
	void Execute(DrawArea layerArea, DrawArea drawArea, int color);
};

#endif //!__VG_DRAW_LABEL_H__
