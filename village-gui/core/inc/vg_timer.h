//###########################################################################
// vg_timer.h
// Declarations of the functions that manage timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TIMER_H__
#define __VG_TIMER_H__

#include "vg_devices.h"
#include "vg_ticks.h"


/// @brief VgTimer
class VgTimer
{
private:
	//Members
	VgDevices&  devices;
	Ticks*      ticks;
	bool        isReady;
public:
	//Methods
	VgTimer(VgDevices& devices);
	~VgTimer();
	void Setup();
	void Execute();
	void Exit();
	void RegisterTick(Ticks* ticks);
	void UnregisterTick(Ticks* ticks);
};

#endif //!__VG_TIMER_H__
