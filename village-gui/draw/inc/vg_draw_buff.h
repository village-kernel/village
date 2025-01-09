//###########################################################################
// vg_draw_buff.h
// Declarations of the functions that about draw buff
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_BUFF_H__
#define __VG_DRAW_BUFF_H__

#include "vg_devices.h"
#include "vg_draw_defs.h"
#include "vg_math.h"


/// @brief VgDrawBuff
class VgDrawBuff
{
private:
	//Members
	VgDevices* devices;

	//Members
	VgMath math;
public:
	//Methods
	void Initiate(VgDevices* devices);
	void Execute(VgDrawArea layerArea, VgDrawArea drawArea, int* buff);
};

#endif //!__VG_DRAW_BUFF_H__
