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
    led.Set();
    System::DelayMs(100);
    led.Clear();
    System::DelayMs(100);
}


///Register module
REGISTER_MODULE(new Application2(), FUNCTION_ID(1U));
