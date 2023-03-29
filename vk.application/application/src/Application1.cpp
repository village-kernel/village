//###########################################################################
// Application1.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application1.h"


/// Constructor
Application1::Application1()
{
}


/// Initialize
void Application1::Initialize()
{
	led.Initialize(Gpio::_ChA, 3, Gpio::_Low);
}


/// Execute
void Application1::Execute()
{
	while (1)
	{
		led.Set();
		Thread::Sleep(500);
		led.Clear();
		Thread::Sleep(500);
	}
}


///Register module
REGISTER_MODULE(new Application1(), (ModuleID::_application + 0), app_1);
