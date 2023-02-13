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
    led.Set();
    System::DelayMs(100);
    led.Clear();
    System::DelayMs(100);
}


///Register module
REGISTER_MODULE(new Application1(), FUNCTION_ID(0));
