//###########################################################################
// Application1.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Thread.h"
#include "Application1.h"

ThreadEndpoint* Application1::user;
ThreadHandlerCpp Application1::handler;


/// Constructor
Application1::Application1()
{
}


/// Initialize
void Application1::Initialize()
{
	led.Initialize(Gpio::_ChA, 3, Gpio::_Low);

	user = this;
	handler = (ThreadHandlerCpp)(&Application1::Task);
	Thread::CreateTask(Application1::TaskHandler);
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


///TaskHandler
void Application1::TaskHandler()
{
	if (user != 0) { (user->*handler)(); }
}


///Register module
REGISTER_MODULE(new Application1(), 1, app_1);
