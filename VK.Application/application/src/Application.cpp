//###########################################################################
// Application.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application.h"
#include "HalHeaders.h"

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


/// Constructor
Application::Application()
{
}


/// Initialize
void Application::Initialize()
{
	HAL_Init();

	__GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_3;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/// Execute
void Application::Execute()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_Delay(100);
}


///Register module
REGISTER_MODULE(new Application(), FUNCTION_ID(0));
