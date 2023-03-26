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

	Thread::CreateTaskCpp(this, (ThreadHandlerCpp)&Application1::Task);
}


/// Execute
void Application1::Execute()
{
	led.Set();
	Thread::Sleep(500);
	led.Clear();
	Thread::Sleep(500);
}


///Task
void Application1::Task()
{
	Gpo led;

	led.Initialize(Gpio::_ChE, 5, Gpio::_Low);

	while(1) 
	{
		led.Set();
		Thread::Sleep(500);
		led.Clear();
		Thread::Sleep(500);
	}
}


///Register module
REGISTER_MODULE(new Application1(), (ModuleID::_application + 0), app_1);
