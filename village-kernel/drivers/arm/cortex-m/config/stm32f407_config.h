//###########################################################################
// stm32f407_config.h
//
// Contains hardware configuration such as pin and peripheral assignments
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_STM32F407_CONFIG_H__
#define __HW_STM32F407_CONFIG_H__


//*********************************Serial*********************************//
#define UART_SERIAL_CONFIG                                                \
{                                                                         \
	.usartCh   = Usart::_Usart1,                                          \
	.baudrate  = 115200,                                                  \
	.enableRTS = false,                                                   \
	.enableDMA = true,                                                    \
                                                                          \
	.txGpio = { Gpio::_ChA, 9,  Gpio::_Alt, 7, 0 },                       \
	.rxGpio = { Gpio::_ChB, 7,  Gpio::_Alt, 7, 0 },                       \
	.deGpio = { 0, 0, 0, 0, 0 },                                          \
                                                                          \
	.txDma = { Dma::_Group2, Dma::_Stream7, 4, NULL, false },             \
	.rxDma = { Dma::_Group2, Dma::_Stream2, 4, NULL, true  },             \
}


//********************************SpiFlash********************************//
#define SPI_FLASH_CONFIG                                                  \
{                                                                         \
	.spiCh    = Spi::_Spi2,                                               \
                                                                          \
	.sckGpio  = { Gpio::_ChB, 13,  Gpio::_Alt,    5,  0 },                \
	.misoGpio = { Gpio::_ChB, 14,  Gpio::_Alt,    5,  0 },                \
	.mosiGpio = { Gpio::_ChB, 15,  Gpio::_Alt,    5,  0 },                \
	.csGpio   = { Gpio::_ChB, 12,  Gpio::_Output, 0,  1 },                \
	.wpGpio   = { Gpio::_ChF, 15,  Gpio::_Output, 0,  1 },                \
}


//********************************SD Card*********************************//
#define SPI_SDCARD_CONFIG                                                 \
{                                                                         \
	.spiCh    = Spi::_Spi3,                                               \
                                                                          \
	.sckGpio  = { Gpio::_ChC, 10, Gpio::_Alt,    6, 0 },                  \
	.misoGpio = { Gpio::_ChC, 11, Gpio::_Alt,    6, 0 },                  \
	.mosiGpio = { Gpio::_ChC, 12, Gpio::_Alt,    6, 0 },                  \
	.csGpio   = { Gpio::_ChB, 5,  Gpio::_Output, 0, 1 },                  \
	.dtGpio   = { Gpio::_ChB, 6,  Gpio::_Output, 0, 0 },                  \
}


//*********************************lcd Pin********************************//
#define LCD_RGB565_CONFIG                                                 \
{                                                                         \
	.blGpio   = { Gpio::_ChG, 8,  Gpio::_Output,  0, 0 },                 \
	.csGpio   = { Gpio::_ChG, 12, Gpio::_Alt,    12, 0 },                 \
	.rsGpio   = { Gpio::_ChF, 12, Gpio::_Alt,    12, 0 },                 \
	.wrGpio   = { Gpio::_ChD, 5,  Gpio::_Alt,    12, 0 },                 \
	.rdGpio   = { Gpio::_ChD, 4,  Gpio::_Alt,    12, 0 },                 \
	.db0Gpio  = { Gpio::_ChD, 14, Gpio::_Alt,    12, 0 },                 \
	.db1Gpio  = { Gpio::_ChD, 15, Gpio::_Alt,    12, 0 },                 \
	.db2Gpio  = { Gpio::_ChD, 0,  Gpio::_Alt,    12, 0 },                 \
	.db3Gpio  = { Gpio::_ChD, 1,  Gpio::_Alt,    12, 0 },                 \
	.db4Gpio  = { Gpio::_ChE, 7,  Gpio::_Alt,    12, 0 },                 \
	.db5Gpio  = { Gpio::_ChE, 8,  Gpio::_Alt,    12, 0 },                 \
	.db6Gpio  = { Gpio::_ChE, 9,  Gpio::_Alt,    12, 0 },                 \
	.db7Gpio  = { Gpio::_ChE, 10, Gpio::_Alt,    12, 0 },                 \
	.db8Gpio  = { Gpio::_ChE, 11, Gpio::_Alt,    12, 0 },                 \
	.db9Gpio  = { Gpio::_ChE, 12, Gpio::_Alt,    12, 0 },                 \
	.db10Gpio = { Gpio::_ChE, 13, Gpio::_Alt,    12, 0 },                 \
	.db11Gpio = { Gpio::_ChE, 14, Gpio::_Alt,    12, 0 },                 \
	.db12Gpio = { Gpio::_ChE, 15, Gpio::_Alt,    12, 0 },                 \
	.db13Gpio = { Gpio::_ChD, 8,  Gpio::_Alt,    12, 0 },                 \
	.db14Gpio = { Gpio::_ChD, 9,  Gpio::_Alt,    12, 0 },                 \
	.db15Gpio = { Gpio::_ChD, 10, Gpio::_Alt,    12, 0 },                 \
}


#endif // !__HW_STM32F407_CONFIG_H__
