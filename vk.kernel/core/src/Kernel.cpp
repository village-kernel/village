//###########################################################################
// Kernel.cpp
// Definitions of the functions that manage Kernel
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"


/// @brief debug
Debug Kernel::debug;

/// @brief memory
Memory Kernel::memory;

/// @brief interrupt
Interrupt Kernel::interrupt;

/// @brief exception
Exception Kernel::exception;

/// @brief environment
Environment Kernel::environment;

/// @brief thread
Thread Kernel::thread;

/// @brief scheduler
Scheduler Kernel::scheduler;

/// @brief device
Device Kernel::device;

/// @brief modular
Modular Kernel::modular;

/// @brief Exprot debug symbol
EXPORT_SYMBOL(_ZN6Kernel5debugE);

/// @brief Exprot memory symbol
EXPORT_SYMBOL(_ZN6Kernel6memoryE);

/// @brief Exprot interrupt symbol
EXPORT_SYMBOL(_ZN6Kernel9interruptE);

/// @brief Exprot exception symbol
EXPORT_SYMBOL(_ZN6Kernel9exceptionE);

/// @brief Exprot environment symbol
EXPORT_SYMBOL(_ZN6Kernel11environmentE);

/// @brief Exprot thread symbol
EXPORT_SYMBOL(_ZN6Kernel6threadE);

/// @brief Exprot scheduler symbol
EXPORT_SYMBOL(_ZN6Kernel9schedulerE);

/// @brief Exprot device symbol
EXPORT_SYMBOL(_ZN6Kernel6deviceE);

/// @brief Exprot modular symbol
EXPORT_SYMBOL(_ZN6Kernel7modularE);


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
}


/// @brief Kernel update params
void Kernel::UpdateParams()
{
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
	device.FailSafe(arg);
	modular.FailSafe(arg);
}
