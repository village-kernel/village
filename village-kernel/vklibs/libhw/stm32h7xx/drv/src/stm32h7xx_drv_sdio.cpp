//###########################################################################
// stm32h7xx_drv_sdio.cpp
// Hardware Layer class that manages a single sdio module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32h7xx_drv_sdio.h"
#include "hardware.h"
#include "Kernel.h"


/// @brief Initialize
/// @param config 
void Sdio::Initialize(Config config)
{
	//Reset the peripheral sdmmc
	RCC->AHB3RSTR |= RCC_AHB3RSTR_SDMMC1RST_Msk;
	RCC->AHB3RSTR &= ~RCC_AHB3RSTR_SDMMC1RST_Msk;

	//Enable the peripheral clock for sdmmc
	RCC->AHB3ENR |= RCC_AHB3ENR_SDMMC1EN_Msk;

	//Select SDMMC kernel clock source: pll2_r_ck
	RCC->D1CCIPR = (RCC->D1CCIPR & ~RCC_D1CCIPR_SDMMCSEL) | (0b01 << RCC_D1CCIPR_SDMMCSEL_Pos);

	//Config pis
	PinConfig(config);

	//SD init
	hsd1.Instance = SDMMC1;
	hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
	hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
	hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
	hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
	hsd1.Init.ClockDiv = 0;

	if (HAL_OK != HAL_SD_Init(&hsd1))
	{
		kernel->debug.Error("SD initialize failed");
	}
}


/// @brief Pin configure
/// @param config 
void Sdio::PinConfig(Config config)
{
	Gpio pin;
	pin.Initialize(config.d0Ch, config.d0Pin, config.d0AltNum, Gpio::_SuperHighSpeed);
	pin.Initialize(config.d1Ch, config.d1Pin, config.d1AltNum, Gpio::_SuperHighSpeed);
	pin.Initialize(config.d2Ch, config.d2Pin, config.d2AltNum, Gpio::_SuperHighSpeed);
	pin.Initialize(config.d3Ch, config.d3Pin, config.d3AltNum, Gpio::_SuperHighSpeed);
	pin.Initialize(config.ckCh, config.ckPin, config.ckAltNum, Gpio::_SuperHighSpeed);
	pin.Initialize(config.cmdCh, config.cmdPin, config.cmdAltNum, Gpio::_SuperHighSpeed);
}


/// @brief Write
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int Sdio::Write(uint8_t* data, uint32_t count, uint32_t blk)
{
	if (HAL_OK == HAL_SD_WriteBlocks_DMA(&hsd1, data, blk, count))
	{
		while (HAL_SD_STATE_READY != hsd1.State)
		{
			HAL_SD_IRQHandler(&hsd1);
		}
		return count;
	}
	return 0;
}


/// @brief Read
/// @param data 
/// @param count 
/// @param blk 
/// @return 
int Sdio::Read(uint8_t* data, uint32_t count, uint32_t blk)
{
	if (HAL_OK == HAL_SD_ReadBlocks_DMA(&hsd1, data, blk, count))
	{
		while (HAL_SD_STATE_READY != hsd1.State)
		{
			HAL_SD_IRQHandler(&hsd1);
		}
		return count;
	}
	return 0;
}
