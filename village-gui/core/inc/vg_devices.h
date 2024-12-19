//###########################################################################
// vg_devices.h
// Declarations of the functions that manage devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DEVICES_H__
#define __VG_DEVICES_H__

#include "vg_ticks.h"
#include "vg_indev.h"
#include "vg_lcddev.h"


/// @brief VgDevices
struct VgDevices
{
	Ticks*  ticks;
	Indev*  indev;
	Lcddev* lcddev;

	VgDevices()
		:ticks(NULL),
		indev(NULL),
		lcddev(NULL)
	{}
};

#endif //!__VG_DEVICES_H__
