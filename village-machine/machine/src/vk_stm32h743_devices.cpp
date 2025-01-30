//###########################################################################
// vk_stm32h743_devices.cpp
// Definitions of the functions that manage devices config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32h743_devices.h"
#include "vk_kernel.h"


/// @brief SdioSdCardDev
void SdioSdCardDev::Config()
{
	config = {
		.d0Gpio  = { Gpio::_ChC, 8,  Gpio::_Altera, 12, 0 },
		.d1Gpio  = { Gpio::_ChC, 9,  Gpio::_Altera, 12, 0 },
		.d2Gpio  = { Gpio::_ChC, 10, Gpio::_Altera, 12, 0 },
		.d3Gpio  = { Gpio::_ChC, 11, Gpio::_Altera, 12, 0 },
		.ckGpio  = { Gpio::_ChC, 12, Gpio::_Altera, 12, 0 },
		.cmdGpio = { Gpio::_ChD, 2,  Gpio::_Altera, 12, 0 },
	};
	driverData = (void*)&config;
	driverName = (char*)"disk0";
}
REGISTER_PLAT_DEVICE(new SdioSdCardDev(), sdioSdCard, sdioSdCardDev);


/// @brief Stm32UartDev
void Stm32UartDev::Config()
{
	config = {
		.usartCh   = Usart::_Usart1,
		.baudrate  = 115200,
		.enableRTS = false,
		.enableDMA = true,

		.txGpio = { Gpio::_ChA, 9,  Gpio::_Altera, 7, 0 },
		.rxGpio = { Gpio::_ChB, 7,  Gpio::_Altera, 7, 0 },
		.deGpio = { 0, 0, 0, 0, 0 },

		.txDma = { Dma::_Group2, Dma::_Stream7, 4, Dma::_MemoryToPeriph, 0 },
		.rxDma = { Dma::_Group2, Dma::_Stream2, 4, Dma::_PeriphToMemory, 0 },
	};
	driverData = (void*)&config;
	driverName = (char*)"serial0";
}
REGISTER_PLAT_DEVICE(new Stm32UartDev(), stm32uart, stm32uartDev);
