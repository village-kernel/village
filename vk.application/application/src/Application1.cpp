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
	exti.ConfigTriggerEdge(Exti::_BothEdge);
	exti.EnableInterrupt();

	interrupt.SetISR(EXTI0_IRQn, union_cast<Function>(&Application1::ExtHandler), (char*)this);
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
		extLed.Toggle();
		exti.Clear();
	}
}


///Register module
REGISTER_MODULE(new Application1(), (ModuleID::_application + 0), app_1);
