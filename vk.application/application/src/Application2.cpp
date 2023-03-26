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

	Thread::CreateTaskCpp(this, (ThreadHandlerCpp)&Application2::Task);
}


/// Execute
void Application2::Execute()
{
	led.Set();
	Thread::Sleep(500);
	led.Clear();
	Thread::Sleep(500);
}


///Task
void Application2::Task()
{
	Gpo led;

	led.Initialize(Gpio::_ChA, 8, Gpio::_Low);

	while (1)
	{
		led.Set();
		Thread::Sleep(500);
		led.Clear();
		Thread::Sleep(500);
	}
}


///Register module
REGISTER_MODULE(new Application2(), (ModuleID::_application + 1), app_2);
