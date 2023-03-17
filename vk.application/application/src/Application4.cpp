//###########################################################################
// Application4.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Application4.h"


void Delay()
{
	for (volatile uint32_t i = 0; i < 1000; i++)
	{
		for (volatile uint32_t j = 0; j < 1000; j++) {}
	}
}


void Application4::Initialize()
{
}


void Application4::Execute()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN_Msk;
	GPIOE->MODER = (GPIOE->MODER & ~GPIO_MODER_MODER5_Msk) | (GPIO_MODER_MODE5_0);

	while(1)
	{
		GPIOE->BSRR |= GPIO_BSRR_BR5;
		Delay();
		GPIOE->BSRR |= GPIO_BSRR_BS5;
		Delay();
	}
}


extern "C" void Entry()
{
	Application4 app;
	app.Initialize();
	app.Execute();
}

