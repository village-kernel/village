//###########################################################################
// vk_drv_sdram.cpp
// Hardware layer class that manages SDRAM module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_sdram.h"


/// @brief SDRAM mode reg defines
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


/// @brief Initialize
/// @param config 
void SDRAM::Initialize()
{
    __HAL_RCC_FMC_CLK_ENABLE();

    hsdram.Instance = FMC_SDRAM_DEVICE;
    hsdram.Init.SDBank = FMC_SDRAM_BANK1;
    hsdram.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
    hsdram.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
    hsdram.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
    hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
    hsdram.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
    hsdram.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
    
    Timing.LoadToActiveDelay = 2;
    Timing.ExitSelfRefreshDelay = 8;
    Timing.SelfRefreshTime = 7;
    Timing.RowCycleDelay = 7;
    Timing.WriteRecoveryTime = 2;
    Timing.RPDelay = 2;
    Timing.RCDDelay = 2;
    HAL_SDRAM_Init(&hsdram, &Timing);
}


/// @brief Write Cmd
void SDRAM::WriteCmd(uint8_t cmd, uint8_t refresh, uint16_t regval)
{
    FMC_SDRAM_CommandTypeDef command;

    command.CommandMode = cmd;
    command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    command.AutoRefreshNumber = refresh;
    command.ModeRegisterDefinition = regval;

    HAL_SDRAM_SendCommand(&hsdram, &command, 0X1000);
}


/// @brief 
void SDRAM::InitSequece()
{
    WriteCmd(FMC_SDRAM_CMD_CLK_ENABLE, 1, 0);
    HAL_Delay(500);
    WriteCmd(FMC_SDRAM_CMD_PALL, 1, 0);
    WriteCmd(FMC_SDRAM_CMD_AUTOREFRESH_MODE, 8, 0);

    uint32_t regval = SDRAM_MODEREG_BURST_LENGTH_1         |
                      SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL  |
                      SDRAM_MODEREG_CAS_LATENCY_2          |
                      SDRAM_MODEREG_OPERATING_MODE_STANDARD|
                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    WriteCmd(FMC_SDRAM_CMD_LOAD_MODE, 1, regval);
}


/// @brief Config Refresh Rate
/// @param rate 
void SDRAM::ConfigRefreshRate(uint32_t rate)
{
    HAL_SDRAM_ProgramRefreshRate(&hsdram, rate); 
}


/// @brief Config address
/// @param address 
void SDRAM::ConfigBankAddress(uint32_t address)
{
    bankAddr = address;
}


/// @brief Write
/// @param data 
/// @param size 
/// @param addr 
void SDRAM::Write(uint8_t* data, uint32_t size, uint32_t addr)
{
    for (uint32_t i = 0; i < size; i++)
    {
        ((volatile uint8_t *)(bankAddr + addr))[i] = data[i];
    }
}


/// @brief Read
/// @param data 
/// @param size 
/// @param addr 
void SDRAM::Read(uint8_t* data, uint32_t size, uint32_t addr)
{
    for (uint32_t i = 0; i < size; i++)
    {
        data[i] = ((volatile uint8_t *)(bankAddr + addr))[i];
    }
}
