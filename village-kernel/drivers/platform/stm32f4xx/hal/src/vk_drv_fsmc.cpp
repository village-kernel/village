//###########################################################################
// vk_drv_fsmc.cpp
// Hardware layer class that manages FSMC module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_fsmc.h"


/// @brief Initialize
void Fsmc::Initialize()
{
	//Enable the peripheral clock for fsmc
	RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN_Msk;

	//Config BCR: Data width 16 bits, memory type SRAM, write enabled
	FSMC_Bank1->BTCR[6] = FSMC_BCR1_MWID_0 | FSMC_BCR1_WREN | FSMC_BCR1_MBKEN;

	//Config BTR: Timing parameter
	//ADDSET=7 (Add Setup), DATAST=7 (Data Setup)
	FSMC_Bank1->BTCR[7] = (7 << 0) | (7 << 8);

	//Calc cmd and data address
	cmdAddr = (volatile uint16_t*)0x6C000000;
	dataAddr = (volatile uint16_t*)(0x6C000000 | (1 << (6 + 1)));
}


/// @brief 
/// @param cmd 
void Fsmc::WriteCmd(uint16_t cmd)
{
	*cmdAddr = cmd;
}


/// @brief 
/// @param data 
void Fsmc::WriteData(uint16_t data)
{
	*dataAddr = data;
}


/// @brief 
/// @return 
uint16_t Fsmc::ReadData()
{
	return *dataAddr;
}
