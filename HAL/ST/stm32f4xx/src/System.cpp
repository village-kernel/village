//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"


///Initialize static members
uint32_t System::sysTicks = 0;
uint32_t System::cyclesInMicro = 8;


///Configure the SysTick timer
void System::Initialize(void)
{
#ifdef PRIVILEGED_LEVEL_DELAY
	//Enable Data Watchpoint and Trace unit and turn on its main counter
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
#endif
	//Select Systick clock source: SYSCLK_MHZ/8 = 168/8 = 21M
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

	//Enable systick interrupt
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	//Set systick reload value
	SysTick->LOAD = 21000;

	//Clear systick current value
	SysTick->VAL = 0;

	//Enable systick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	//Calculate the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}


///Configure memory protection unit
void System::ConfigureMPU()
{

}


///Configure the main internal regulator output voltage
void System::ConfigurePower()
{
	//Select regulator voltage output Scale 1 mode
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;
}


///Select using HSI or HSE as system clock
void System::ConfigureClock()
{
	ConfigureForXtal();
}


///Configures the system to use an hsi crystal as clock source.
///HSI：16Mhz, PLL: 168Mhz, System Clock = PLL1, PCLK1 = 42Mhz, PCLK2=84Mhz.
void System::ConfigureForHsi()
{
	const uint32_t pll_m = 8;
	const uint32_t pll_n = 168;
	const uint32_t pll_p = 2;
	const uint32_t pll_q = 7;

	//Enable HSI
	RCC->CR |= ((uint32_t)RCC_CR_HSION);
	while ((RCC->CR & RCC_CR_HSIRDY_Msk) != RCC_CR_HSIRDY);

	//Configure the main PLL
	RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_HSI) |
					(pll_m << RCC_PLLCFGR_PLLM_Pos) |
					(pll_n << RCC_PLLCFGR_PLLN_Pos) |
					(((pll_p >> 1u) - 1u) << RCC_PLLCFGR_PLLP_Pos) |
					(pll_q << RCC_PLLCFGR_PLLQ_Pos);

	//Enable the main PLL
	RCC->CR |= RCC_CR_PLLON;

	//Wait till the main PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}

	//Configure Flash prefetch, Instruction cache, Data cache and wait state
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

	//HCLK = SYSCLK / 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	//PCLK1 = HCLK / 4
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	//PCLK2 = HCLK / 2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	//Select the main PLL as system clock source
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	//Wait till the main PLL is used as system clock source
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}

	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//Update the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}


///Configures the system to use an hse crystal as clock source.
///XTAL：8Mhz, PLL: 168Mhz, System Clock = PLL1, PCLK1 = 42Mhz, PCLK2=84Mhz.
void System::ConfigureForXtal()
{
	const uint32_t pll_m = 4;
	const uint32_t pll_n = 168;
	const uint32_t pll_p = 2;
	const uint32_t pll_q = 7;

	//Enable HSE
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	while ((RCC->CR & RCC_CR_HSERDY_Msk) != RCC_CR_HSERDY);

	//Configure the main PLL
	RCC->PLLCFGR = (RCC_PLLCFGR_PLLSRC_HSE) |
					(pll_m << RCC_PLLCFGR_PLLM_Pos) |
					(pll_n << RCC_PLLCFGR_PLLN_Pos) |
					(((pll_p >> 1u) - 1u) << RCC_PLLCFGR_PLLP_Pos) |
					(pll_q << RCC_PLLCFGR_PLLQ_Pos);

	//Enable the main PLL
	RCC->CR |= RCC_CR_PLLON;

	//Wait till the main PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}

	//Configure Flash prefetch, Instruction cache, Data cache and wait state
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

	//HCLK = SYSCLK / 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	//PCLK1 = HCLK / 4
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	//PCLK2 = HCLK / 2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	//Select the main PLL as system clock source
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	//Wait till the main PLL is used as system clock source
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}

	//Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//Update the cyclesInMicro variable
	cyclesInMicro = SystemCoreClock / microsInSec;
}


///Systick handler
extern "C" __weak void SysTick_Handler(void)
{
	System::SysTickCounter();
}
