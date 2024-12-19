//###########################################################################
// vg_screen.h
// Declarations of the functions that manage screen
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_SCREEN_H__
#define __VG_SCREEN_H__

#include "vg_devices.h"
#include "vg_lcddev.h"
#include "vg_list.h"


/// @brief VgScreen
class VgScreen
{
private:
	//Members
	VgDevices&       devices;
	VgList<Lcddev*>  lcddevs;
	bool             isReady;
public:
	//Methods
	VgScreen(VgDevices& devices);
	~VgScreen();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	void RegisterLcddev(Lcddev* lcd);
	void UnregisterLcddev(Lcddev* lcd);
};

#endif //!__VG_SCREEN_H__
