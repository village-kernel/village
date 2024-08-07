//###########################################################################
// stm32h7xx_drv_sdio.cpp
// Hardware Layer class that manages a single sdio module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32h7xx_drv_sdio.h"
#include "hardware.h"
#include "Kernel.h"


/// @brief Static members
SD_HandleTypeDef Sdio::hsd;
volatile uint8_t Sdio::writeStatus = 0;
volatile uint8_t Sdio::readStatus = 0;


/// @brief Initialize
/// @param config 
uint8_t Sdio::Initialize()
{
	uint8_t state = MSD_OK;

	//Reset the peripheral sdmmc
	RCC->AHB3RSTR |= RCC_AHB3RSTR_SDMMC1RST_Msk;
	RCC->AHB3RSTR &= ~RCC_AHB3RSTR_SDMMC1RST_Msk;

	//Enable the peripheral clock for sdmmc
	RCC->AHB3ENR |= RCC_AHB3ENR_SDMMC1EN_Msk;

	//Select SDMMC kernel clock source: pll2_r_ck
	RCC->D1CCIPR = (RCC->D1CCIPR & ~RCC_D1CCIPR_SDMMCSEL) | (0b01 << RCC_D1CCIPR_SDMMCSEL_Pos);

	//Config interrupt
	HAL_NVIC_SetPriority(SDMMC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);

	//SD config
	hsd.Instance = SDMMC1;
	hsd.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
	hsd.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
	hsd.Init.BusWide = SDMMC_BUS_WIDE_4B;
	hsd.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
	hsd.Init.ClockDiv = 0;
	
	//HAL SD initialization
	state = HAL_SD_Init(&hsd);

	//Configure SD Bus width (4 bits mode selected)
	if (state == MSD_OK)
	{
		//Enable wide operation
		if (HAL_SD_ConfigWideBusOperation(&hsd, SDMMC_BUS_WIDE_4B) != HAL_OK)
		{
			state = MSD_ERROR;
		}
	}

	return state;
}


/// @brief Sdio Uninitialize
uint8_t Sdio::Uninitialize()
{
	HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
	return 0;
}


/// @brief WriteBlocks
/// @param data 
/// @param count 
/// @param blk 
/// @return 
uint8_t Sdio::WriteBlocks(uint8_t* data, uint32_t count, uint32_t blk, uint32_t timeout)
{
	uint8_t state = MSD_OK;

	if (HAL_SD_WriteBlocks(&hsd, data, blk, count, timeout) != HAL_OK)
	{
		state = MSD_ERROR;
	}

	return state;
}


/// @brief ReadBlocks
/// @param data 
/// @param count 
/// @param blk 
/// @return 
uint8_t Sdio::ReadBlocks(uint8_t* data, uint32_t count, uint32_t blk, uint32_t timeout)
{
	uint8_t state = MSD_OK;

	if (HAL_SD_ReadBlocks(&hsd, data, blk, count, timeout) != HAL_OK)
	{
		state = MSD_ERROR;
	}

	return state;
}


/// @brief WriteBlocksDMA
/// @param data 
/// @param count 
/// @param blk 
/// @return 
uint8_t Sdio::WriteBlocksDMA(uint8_t* data, uint32_t count, uint32_t blk)
{
	uint8_t state = MSD_OK;

	//Write block(s) in DMA transfer mode
	if (HAL_SD_WriteBlocks_DMA(&hsd, data, blk, count) != HAL_OK)
	{
		state = MSD_ERROR;
	}

	return state;
}


/// @brief ReadBlocksDMA
/// @param data 
/// @param count 
/// @param blk 
/// @return 
uint8_t Sdio::ReadBlocksDMA(uint8_t* data, uint32_t count, uint32_t blk)
{
	uint8_t state = MSD_OK;

	//Read block(s) in DMA transfer mode
	if (HAL_SD_ReadBlocks_DMA(&hsd, data, blk, count) != HAL_OK)
	{
		state = MSD_ERROR;
	}

	return state;
}


/// @brief Erase
/// @param startAddr 
/// @param endAddr 
/// @return 
uint8_t Sdio::Erase(uint32_t startAddr, uint32_t endAddr)
{
	uint8_t state = MSD_OK;

	if (HAL_SD_Erase(&hsd, startAddr, endAddr) != HAL_OK)
	{
		state = MSD_ERROR;
	}

	return state;
}


/// @brief GetCardState
/// @param  
/// @return 
uint8_t Sdio::GetCardState()
{
	return ((HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}


/// @brief GetCardInfo
/// @param CardInfo 
void Sdio::GetCardInfo(SDCardInfo *cardInfo)
{
	//Get SD card Information
	HAL_SD_GetCardInfo(&hsd, (HAL_SD_CardInfoTypeDef*)cardInfo);
}


/// @brief ClearWriteStatus
void Sdio::ClearWriteStatus() { writeStatus = false; }


/// @brief SetWriteStatus
void Sdio::SetWriteStatus() { writeStatus = true; }


/// @brief ClearReadStatus
void Sdio::ClearReadStatus() { readStatus = false; }


/// @brief SetReadStatus
void Sdio::SetReadStatus() { readStatus = true; }


/// @brief GetWriteStatus
/// @return 
bool Sdio::GetWriteStatus() { return writeStatus; }


/// @brief GetReadStatus
/// @return 
bool Sdio::GetReadStatus() { return readStatus; }


/// @brief IRQHandler
void Sdio::IRQHandler() { HAL_SD_IRQHandler(&hsd); }


/// @brief HAL_SD_TxCpltCallback
/// @param hsd 
extern "C" void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
	Sdio::SetWriteStatus();
}


/// @brief HAL_SD_RxCpltCallback
/// @param hsd 
extern "C" void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
	Sdio::SetReadStatus();
}


/// @brief IRQHandler
/// @param  
extern "C" void SDMMC1_IRQHandler()
{
	Sdio::IRQHandler();
}
