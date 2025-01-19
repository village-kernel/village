//###########################################################################
// vk_stm32f407_devices.cpp
// Definitions of the functions that manage devices config
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_stm32f407_devices.h"
#include "vk_kernel.h"


/// @brief SpiSdCardDev
void SpiSdCardDev::Config()
{
	config = {
		.spiCh    = Spi::_Spi3,
		.sckGpio  = { Gpio::_ChC, 10, Gpio::_Altera, 6, 0 },
		.misoGpio = { Gpio::_ChC, 11, Gpio::_Altera, 6, 0 },
		.mosiGpio = { Gpio::_ChC, 12, Gpio::_Altera, 6, 0 },
		.csGpio   = { Gpio::_ChB, 5,  Gpio::_Output, 0, 1 },
		.dtGpio   = { Gpio::_ChB, 6,  Gpio::_Output, 0, 0 },
	};
	driverData = (void*)&config;
	driverName = (char*)"disk0";
}
REGISTER_PLAT_DEVICE(new SpiSdCardDev(), spiSdCard, spiSdCardDev);


/// @brief SpiW25Q64Dev
void SpiW25Q64Dev::Config()
{
	config = {
		.spiCh    = Spi::_Spi2,
		.sckGpio  = { Gpio::_ChB, 13,  Gpio::_Altera, 5,  0 },
		.misoGpio = { Gpio::_ChB, 14,  Gpio::_Altera, 5,  0 },
		.mosiGpio = { Gpio::_ChB, 15,  Gpio::_Altera, 5,  0 },
		.csGpio   = { Gpio::_ChB, 12,  Gpio::_Output, 0,  1 },
		.wpGpio   = { Gpio::_ChF, 15,  Gpio::_Output, 0,  1 },
		.deviceID = 0xEF16,
	};
	driverData = (void*)&config;
	driverName = (char*)"disk1";
}
REGISTER_PLAT_DEVICE(new SpiW25Q64Dev(), spiW25qxx, spiW25Q64Dev);


/// @brief ILI9488Dev
void ILI9488Dev::Config()
{
	config = {
		.blGpio   = { Gpio::_ChG, 8,  Gpio::_Output,  0, 0 },
		.csGpio   = { Gpio::_ChG, 12, Gpio::_Altera, 12, 0 },
		.rsGpio   = { Gpio::_ChF, 12, Gpio::_Altera, 12, 0 },
		.wrGpio   = { Gpio::_ChD, 5,  Gpio::_Altera, 12, 0 },
		.rdGpio   = { Gpio::_ChD, 4,  Gpio::_Altera, 12, 0 },
		.db0Gpio  = { Gpio::_ChD, 14, Gpio::_Altera, 12, 0 },
		.db1Gpio  = { Gpio::_ChD, 15, Gpio::_Altera, 12, 0 },
		.db2Gpio  = { Gpio::_ChD, 0,  Gpio::_Altera, 12, 0 },
		.db3Gpio  = { Gpio::_ChD, 1,  Gpio::_Altera, 12, 0 },
		.db4Gpio  = { Gpio::_ChE, 7,  Gpio::_Altera, 12, 0 },
		.db5Gpio  = { Gpio::_ChE, 8,  Gpio::_Altera, 12, 0 },
		.db6Gpio  = { Gpio::_ChE, 9,  Gpio::_Altera, 12, 0 },
		.db7Gpio  = { Gpio::_ChE, 10, Gpio::_Altera, 12, 0 },
		.db8Gpio  = { Gpio::_ChE, 11, Gpio::_Altera, 12, 0 },
		.db9Gpio  = { Gpio::_ChE, 12, Gpio::_Altera, 12, 0 },
		.db10Gpio = { Gpio::_ChE, 13, Gpio::_Altera, 12, 0 },
		.db11Gpio = { Gpio::_ChE, 14, Gpio::_Altera, 12, 0 },
		.db12Gpio = { Gpio::_ChE, 15, Gpio::_Altera, 12, 0 },
		.db13Gpio = { Gpio::_ChD, 8,  Gpio::_Altera, 12, 0 },
		.db14Gpio = { Gpio::_ChD, 9,  Gpio::_Altera, 12, 0 },
		.db15Gpio = { Gpio::_ChD, 10, Gpio::_Altera, 12, 0 },
	};
	driverData = (void*)&config;
	driverName = (char*)"display0";
}
REGISTER_PLAT_DEVICE(new ILI9488Dev(), ili9488, ili9488Dev);


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


/// @brief Stm32UsbDev
void Stm32UsbDev::Config()
{
	config = {
		.dmGpio = { Gpio::_ChA, 11,  Gpio::_Altera, 10, 0 },
		.dpGpio = { Gpio::_ChA, 12,  Gpio::_Altera, 10, 0 },
	};
	driverData = (void*)&config;
	driverName = (char*)"usb0";
}
REGISTER_PLAT_DEVICE(new Stm32UsbDev(), stm32Usb, stm32UsbDev);
