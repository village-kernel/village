//###########################################################################
// stm32f4xx_drv_fsmc.cpp
// Hardware layer class that manages FSMC module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32f4xx_drv_fsmc.h"


///Initialize
void Fsmc::Initialize(Config config)
{
	//Config pins
	PinConfig(config);

	//Enable the peripheral clock for fsmc
	RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN_Msk;

	SRAM_HandleTypeDef hsram4;
	FSMC_NORSRAM_TimingTypeDef Timing = {0};

	//Perform the SRAM4 memory initialization sequence
	hsram4.Instance = FSMC_NORSRAM_DEVICE;
	hsram4.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	//hsram4.Init
	hsram4.Init.NSBank = FSMC_NORSRAM_BANK4;
	hsram4.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	hsram4.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
	hsram4.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	hsram4.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	hsram4.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	hsram4.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	hsram4.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	hsram4.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	hsram4.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	hsram4.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	hsram4.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	hsram4.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	hsram4.Init.PageSize = FSMC_PAGE_SIZE_NONE;
	//Timing
	Timing.AddressSetupTime = 7;
	Timing.AddressHoldTime = 0;
	Timing.DataSetupTime = 7;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 0;
	Timing.DataLatency = 0;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;

	HAL_SRAM_Init(&hsram4, &Timing, NULL);
}


///Pin configure
void Fsmc::PinConfig(Config config)
{
	Gpio pin;
	pin.Initialize(config.csCh, config.csPin, pin_alt_num);
	pin.Initialize(config.rsCh, config.rsPin, pin_alt_num);
	pin.Initialize(config.wrCh, config.wrPin, pin_alt_num);
	pin.Initialize(config.rdCh, config.rdPin, pin_alt_num);
	pin.Initialize(config.db0Ch, config.db0Pin, pin_alt_num);
	pin.Initialize(config.db1Ch, config.db1Pin, pin_alt_num);
	pin.Initialize(config.db2Ch, config.db2Pin, pin_alt_num);
	pin.Initialize(config.db3Ch, config.db3Pin, pin_alt_num);
	pin.Initialize(config.db4Ch, config.db4Pin, pin_alt_num);
	pin.Initialize(config.db5Ch, config.db5Pin, pin_alt_num);
	pin.Initialize(config.db6Ch, config.db6Pin, pin_alt_num);
	pin.Initialize(config.db7Ch, config.db7Pin, pin_alt_num);
	pin.Initialize(config.db8Ch, config.db8Pin, pin_alt_num);
	pin.Initialize(config.db9Ch, config.db9Pin, pin_alt_num);
	pin.Initialize(config.db10Ch, config.db10Pin, pin_alt_num);
	pin.Initialize(config.db11Ch, config.db11Pin, pin_alt_num);
	pin.Initialize(config.db12Ch, config.db12Pin, pin_alt_num);
	pin.Initialize(config.db13Ch, config.db13Pin, pin_alt_num);
	pin.Initialize(config.db14Ch, config.db14Pin, pin_alt_num);
	pin.Initialize(config.db15Ch, config.db15Pin, pin_alt_num);
}
