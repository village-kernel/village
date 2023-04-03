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
	Memory::Instance().Initialize();

	//Initialize thread
	Thread::Instance().Initialize();

	//Initialize device
	Device::Instance().Initialize();

	//Initialize modular
	Modular::Instance().Initialize();

	isReady = true;
}


///Execute module object->UpdateParams
void Kernel::UpdateParams()
{
	if (!isReady) return;

	Device::Instance().UpdateParams();
	Modular::Instance().UpdateParams();
}


///Execute thread tasks 
void Kernel::Execute()
{
	//Execute modular
	Modular::Instance().Execute();

	//Start scheduler
	Scheduler::Instance().StartScheduler();

	//Should not go to here
	while (1) {}
}


///Execute module object->FailSafe
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	Device::Instance().FailSafe(arg);
	Modular::Instance().FailSafe(arg);
}
