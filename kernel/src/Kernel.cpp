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
	Memory::Initialize();

	//Initialize thread
	Thread::Initialize();

	//Initialize device
	Device::Initialize();

	//Initialize modular
	Modular::Initialize();

	isReady = true;
}


///Execute module object->UpdateParams
void Kernel::UpdateParams()
{
	if (!isReady) return;

	Device::UpdateParams();
	Modular::UpdateParams();
}


///Execute thread tasks 
void Kernel::Execute()
{
	//Execute device
	Device::Execute();

	//Execute modular
	Modular::Execute();

	//Start scheduler
	Scheduler::StartScheduler();

	//Should not go to here
	while (1) {}
}


///Execute module object->FailSafe
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	Device::FailSafe(arg);
	Modular::FailSafe(arg);
}
