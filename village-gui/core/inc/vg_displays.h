//###########################################################################
// vg_displays.h
// Declarations of the functions that manage displays
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DISPLAYS_H__
#define __VG_DISPLAYS_H__

#include "vg_devices.h"
#include "vg_lcddev.h"
#include "vg_list.h"


/// @brief VgDisplays
class VgDisplays
{
private:
	//Members
	VgDevices&       devices;
	VgList<Lcddev*>  lcddevs;
	bool             isReady;
public:
	//Methods
	VgDisplays(VgDevices& devices);
	~VgDisplays();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	void RegisterLcddev(Lcddev* lcd);
	void UnregisterLcddev(Lcddev* lcd);
};

#endif //!__VG_DISPLAYS_H__
