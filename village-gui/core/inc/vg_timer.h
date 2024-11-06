//###########################################################################
// vg_timer.h
// Declarations of the functions that manage timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TIMER_H__
#define __VG_TIMER_H__

#include "vg_data.h"
#include "vg_ticks.h"


/// @brief GraphicsTimer
class GraphicsTimer
{
private:
	//Members
	GraphicsData&  databus;
	Ticks*         ticks;
	bool           isReady;
public:
	//Methods
	GraphicsTimer(GraphicsData& databus);
	~GraphicsTimer();
	void Setup();
	void Execute();
	void Exit();
	void RegisterTick(Ticks* ticks);
	void UnregisterTick(Ticks* ticks);
};

#endif //!__VG_TIMER_H__
