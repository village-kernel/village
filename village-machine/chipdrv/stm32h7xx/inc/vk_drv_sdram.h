//###########################################################################
// vk_drv_sdram.h
// Hardware layer class that manages SDRAM module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_SDRAM_H__
#define __VK_DRV_SDRAM_H__

#include "vk_hardware.h"


/// @brief SDRAM
class SDRAM
{
private:
    //Members
    SDRAM_HandleTypeDef hsdram = {0};
    FMC_SDRAM_TimingTypeDef Timing = {0};
    volatile uint32_t bankAddr;

    //Methods
    void WriteCmd(uint8_t cmd, uint8_t refresh, uint16_t regval);
public:
	//Methods
	void Initialize();
    void InitSequece();
    void ConfigRefreshRate(uint32_t rate);
    void ConfigBankAddress(uint32_t address);
    void Write(uint8_t* data, uint32_t size, uint32_t addr);
    void Read(uint8_t* data, uint32_t size, uint32_t addr);
};

#endif //!__VK_DRV_SDRAM_H__
