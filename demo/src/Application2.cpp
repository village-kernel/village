//###########################################################################
// Application2.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application2.h"


/// Constructor
Application2::Application2()
{
}


/// Initialize
void Application2::Initialize()
{
	led.Initialize(Gpio::_ChB, 1, Gpio::_Low);
}


/// Execute
void Application2::Execute()
{
	while (1)
	{
		led.Set();
		thread.Sleep(500);
		led.Clear();
		thread.Sleep(500);
	}
}


///Register module
REGISTER_MODULE(new Application2(), (ModuleID::_application + 1), app_2);
