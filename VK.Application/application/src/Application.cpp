//###########################################################################
// Application.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application.h"
#include "HalHeaders.h"


/// Constructor
Application::Application()
{
}


/// Initialize
void Application::Initialize()
{
    led.Initialize(Gpio::_ChA, 3, Gpio::_Low);
}


/// Execute
void Application::Execute()
{
    led.Set();
    System::DelayMs(100);
    led.Clear();
    System::DelayMs(100);
}


///Register module
REGISTER_MODULE(new Application(), FUNCTION_ID(0));
