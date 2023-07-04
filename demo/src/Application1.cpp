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
	extLed.Initialize(Gpio::_ChA, 8, Gpio::_Low);
	extKey.Initialize(Gpio::_ChE, 0);

	exti.Initialize(0);
	exti.ConfigExtPin(Gpio::_ChE, 0);
	exti.ConfigMode(Exti::_Interrupt);
	exti.ConfigTriggerEdge(Exti::_Rising);
	exti.EnableInterrupt();

	interrupt.SetISR(EXTI0_IRQn, (Method)&Application1::ExtHandler, this);
	work = workQueue.Create((Method)&Application1::WorkHandler, this, NULL, work_delay);
}


/// Execute
void Application1::Execute()
{
	while (1)
	{
		led.Set();
		thread.Sleep(500);
		led.Clear();
		thread.Sleep(500);
	}
}


///Ext handler
void Application1::ExtHandler()
{
	if (exti.Check())
	{
		workQueue.Schedule(work);
		exti.Clear();
	}
}


///Work handler
void Application1::WorkHandler()
{
	if (Gpio::_High == extKey.Read())
	{
		extLed.Toggle();
	}
}


///Register module
REGISTER_MODULE(new Application1(), (ModuleID::_application + 0), app_1);
