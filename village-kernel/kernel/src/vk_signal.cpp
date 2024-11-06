//###########################################################################
// vk_signal.cpp
// Definitions of the functions that manage signal
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_signal.h"


/// @brief Constructor
ConcreteSignal::ConcreteSignal()
{
}


/// @brief Destructor
ConcreteSignal::~ConcreteSignal()
{
}


/// @brief Signal setup
void ConcreteSignal::Setup()
{

}


/// @brief Signal exit
void ConcreteSignal::Exit()
{

}


/// @brief Raising
/// @param signal 
void ConcreteSignal::Raising(int signal)
{
	kernel->system.DisableIRQ();

	if (Signals::_Sleep == signal)
	{
		kernel->system.Sleep();
	}
	else if (Signals::_Standby == signal)
	{
		kernel->system.Standby();
	}
	else if (Signals::_Shutdown == signal)
	{
		kernel->Exit();
		kernel->system.Shutdown();
	}
	else if (Signals::_Reboot == signal)
	{
		kernel->Exit();
		kernel->system.Reboot();
	}

	kernel->system.EnableIRQ();
}
