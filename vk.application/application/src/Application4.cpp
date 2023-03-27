//###########################################################################
// Application4.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application4.h"


///Constructor
Application4::Application4()
{
}


///Application4 initialize
void Application4::Initialize()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN_Msk;
	GPIOE->MODER = (GPIOE->MODER & ~GPIO_MODER_MODER5_Msk) | (GPIO_MODER_MODE5_0);
}


///Application4 execute
void Application4::Execute()
{
	GPIOE->BSRR |= GPIO_BSRR_BR5;
	Thread::Sleep(500);
	GPIOE->BSRR |= GPIO_BSRR_BS5;
	Thread::Sleep(500);
}


///Application4 entry
extern "C" void Entry()
{
	Application4 app;
	app.Initialize();
	app.Execute();
}


//Register module
REGISTER_MODULE(new Application4(), (ModuleID::_application + 4), app_4);
