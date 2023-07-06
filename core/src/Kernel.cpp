//###########################################################################
// Kernel.cpp
// Definitions of the functions that manage Kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"


/// @brief Clear isReady flag
volatile bool Kernel::isReady = false;


/// @brief Kernel constructor
Kernel::Kernel()
{
}


/// @brief Kernel deconstructor
Kernel::~Kernel()
{
}


/// @brief Kernel Execute
void Kernel::Initialize()
{
	isReady = false;

	//Initialize memory
	memory.Initialize();

	//Initialize interrupt
	interrupt.Initialize();

	//Initialize exception
	exception.Initialize();

	//Initialize thread
	thread.Initialize();

	//Initialize scheduler
	scheduler.Initialize();

	//Initialize device
	device.Initialize();

	//Initialize modular
	modular.Initialize();

	isReady = true;
}


/// @brief Kernel update params
void Kernel::UpdateParams()
{
	if (!isReady) return;

	device.UpdateParams();
	modular.UpdateParams();
}


/// @brief Kernel execute
void Kernel::Execute()
{
	//Execute device
	device.Execute();

	//Execute modular
	modular.Execute();

	//Start scheduler
	scheduler.Execute();

	//Should not go to here
	while (1) {}
}


/// @brief Kernel failsafe
/// @param arg fail arg
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	device.FailSafe(arg);
	modular.FailSafe(arg);
}
