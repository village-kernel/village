//###########################################################################
// vg_draw_line.h
// Declarations of the functions that about draw line
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_LINE_H__
#define __VG_DRAW_LINE_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"


/// @brief VgDrawLine
class VgDrawLine
{
private:
	//Members
	VgDevices* devices;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, int color);
};

#endif //!__VG_DRAW_LINE_H__
