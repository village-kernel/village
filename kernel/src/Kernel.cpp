//###########################################################################
// kernel.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "kernel.h"


///Clear isReady flag
volatile bool Kernel::isReady = false;


///Constructor
Kernel::Kernel()
{
}


///Execute module object->Initialize
void Kernel::Initialize()
{
	isReady = false;

	//Initialize memory
	memory.Initialize();

	//Initialize thread
	thread.Initialize();

	//Initialize device
	device.Initialize();

	//Initialize modular
	modular.Initialize();

	isReady = true;
}


///Execute module object->UpdateParams
void Kernel::UpdateParams()
{
	if (!isReady) return;

	device.UpdateParams();
	modular.UpdateParams();
}


///Execute thread tasks 
void Kernel::Execute()
{
	//Execute modular
	modular.Execute();

	//Start scheduler
	scheduler.StartScheduler();

	//Should not go to here
	while (1) {}
}


///Execute module object->FailSafe
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	device.FailSafe(arg);
	modular.FailSafe(arg);
}
