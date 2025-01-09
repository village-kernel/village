//###########################################################################
// vg_timer.cpp
// Definitions of the functions that manage tick
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_timer.h"


/// @brief Constructor
VgTimer::VgTimer(VgDevices& devices)
	:devices(devices),
	ticks(NULL),
	isReady(false)
{
}


/// @brief Destructor
VgTimer::~VgTimer()
{
}


/// @brief 
void VgTimer::Setup()
{
	isReady = false;

	if (NULL != ticks)
	{
		ticks->Setup(&devices);

		devices.ticks = ticks;
	}

	isReady = true;
}


/// @brief 
void VgTimer::Execute()
{
	if (NULL != ticks)
	{
		devices.ticks = ticks;
	}
}


/// @brief 
void VgTimer::Exit()
{
	if (NULL != ticks)
	{
		ticks->Exit();
		ticks = NULL;
	}
}


/// @brief 
/// @param tick 
void VgTimer::SetTicks(VgTicks* ticks)
{
	if (NULL != ticks && ticks != this->ticks)
	{
		this->ticks = ticks;
		if (isReady) ticks->Setup(&devices);
	}
}


/// @brief 
/// @param tick 
void VgTimer::ClearTick(VgTicks* ticks)
{
	if (this->ticks == ticks)
	{
		if (isReady) ticks->Exit();
		this->ticks = NULL;
	}
}
