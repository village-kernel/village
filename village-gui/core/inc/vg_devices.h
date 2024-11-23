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


/// @brief GraphicsDevices
struct GraphicsDevices
{
	Ticks*  ticks;
	Indev*  indev;
	Lcddev* lcddev;

	GraphicsDevices()
		:ticks(NULL),
		indev(NULL),
		lcddev(NULL)
	{}
};

#endif //!__VG_DEVICES_H__
