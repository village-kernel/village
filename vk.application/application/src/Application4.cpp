//###########################################################################
// Application4.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Application4.h"
#include "Thread.h"


void Application4::Initialize()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN_Msk;
	GPIOE->MODER = (GPIOE->MODER & ~GPIO_MODER_MODER5_Msk) | (GPIO_MODER_MODE5_0);
}


void Application4::Execute()
{
	while(1)
	{
		GPIOE->BSRR |= GPIO_BSRR_BR5;
		Thread::Sleep(500);
		GPIOE->BSRR |= GPIO_BSRR_BS5;
		Thread::Sleep(500);
	}
}


extern "C" void Entry()
{
	Application4 app;
	app.Initialize();
	app.Execute();
}

