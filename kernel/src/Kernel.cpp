//###########################################################################
// kernel.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "kernel.h"


/// @brief Clear isReady flag
volatile bool Kernel::isReady = false;


/// @brief Constructor
Kernel::Kernel()
{
}


/// @brief Execute module object->Initialize
void Kernel::Initialize()
{
	isReady = false;

	//Initialize memory
	memory.Initialize();

	//Initialize interrupt
	interrupt.Initialize();

	//Initialize thread
	thread.Initialize();

	//Initialize device
	device.Initialize();

	//Initialize modular
	modular.Initialize();

	isReady = true;
}


/// @brief Execute module object->UpdateParams
void Kernel::UpdateParams()
{
	if (!isReady) return;

	device.UpdateParams();
	modular.UpdateParams();
}


/// @brief Execute thread tasks 
void Kernel::Execute()
{
	//Execute modular
	modular.Execute();

	//Start scheduler
	scheduler.StartScheduler();

	//Should not go to here
	while (1) {}
}


/// @brief Execute module object->FailSafe
/// @param arg fail arg
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	device.FailSafe(arg);
	modular.FailSafe(arg);
}
