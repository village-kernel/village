//###########################################################################
// vg_indevs.h
// Declarations of the functions that manage indevs
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INDEVS_H__
#define __VG_INDEVS_H__

#include "vg_devices.h"
#include "vg_indev.h"
#include "vg_list.h"


/// @brief VgIndevs
class VgIndevs
{
private:
	//Members
	VgDevices&      devices;
	VgList<Indev*>  indevs;
	bool            isReady;
public:
	//Methods
	VgIndevs(VgDevices& devices);
	~VgIndevs();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	void RegisterIndev(Indev* indev);
	void UnregisterIndev(Indev* indev);
};

#endif //!__VG_INDEVS_H__