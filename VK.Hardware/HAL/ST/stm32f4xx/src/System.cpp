//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"

uint32_t System::cyclesInMicro = 8;


///Configure the SysTick timer
void System::Initialize(void)
{
	//Enable Data Watchpoint and Trace unit and turn on its main counter
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

	//Select Systick clock source: SYSCLK_MHZ/8 = 480/8 = 60M
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

	//Calculate the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}


///Configures the system to use an hsi crystal as clock source.
///PLL1: 480Mhz, PLL2 = 84Mhz, System Clock = PLL1.
void System::ConfigureForHsi()
{
	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//Update the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}


///Configures the system to use an hse crystal as clock source.
///XTAL：48Mhz, PLL1: 480Mhz, PLL2 = 84Mhz, System Clock = PLL1.
void System::ConfigureForXtal()
{
	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//Update the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}
