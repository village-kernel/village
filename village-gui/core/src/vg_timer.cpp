//###########################################################################
// vg_timer.cpp
// Definitions of the functions that manage tick
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_timer.h"


/// @brief Constructor
GraphicsTimer::GraphicsTimer(GraphicsDevices& devices)
	:devices(devices),
	ticks(NULL),
	isReady(false)
{
}


/// @brief Destructor
GraphicsTimer::~GraphicsTimer()
{
}


/// @brief 
void GraphicsTimer::Setup()
{
	isReady = false;

	if (NULL != ticks) ticks->Setup();

	devices.ticks = ticks;

	isReady = true;
}


/// @brief 
void GraphicsTimer::Execute()
{
	if (NULL != ticks)
	{
		devices.ticks = ticks;
	}
}


/// @brief 
void GraphicsTimer::Exit()
{
	if (NULL != ticks)
	{
		ticks->Exit();
		ticks = NULL;
	}
}


/// @brief 
/// @param tick 
void GraphicsTimer::RegisterTick(Ticks* ticks)
{
	if (NULL != ticks && ticks != this->ticks)
	{
		this->ticks = ticks;
		if (isReady) ticks->Setup();
	}
}


/// @brief 
/// @param tick 
void GraphicsTimer::UnregisterTick(Ticks* ticks)
{
	if (this->ticks == ticks)
	{
		if (isReady) ticks->Exit();
		this->ticks = NULL;
	}
}
