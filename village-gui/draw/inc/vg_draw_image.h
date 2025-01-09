//###########################################################################
// vg_draw_image.h
// Declarations of the functions that about draw image
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_IMAGE_H__
#define __VG_DRAW_IMAGE_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"


/// @brief VgDrawImage
class VgDrawImage
{
private:
	//Members
	VgDevices* devices;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, int color);
};

#endif //!__VG_DRAW_IMAGE_H__
