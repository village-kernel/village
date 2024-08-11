//###########################################################################
// stm32h743_config.h
//
// Contains hardware configuration such as pin and peripheral assignments
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_STM32H743_CONFIG_H__
#define __HW_STM32H743_CONFIG_H__


//*********************************Serial*********************************//
#define UART_SERIAL_CONFIG                                                \
{                                                                         \
	.usartCh   = Usart::_Usart1,                                          \
	.baudrate  = 115200,                                                  \
	.enableRTS = false,                                                   \
	.enableDMA = true,                                                    \
                                                                          \
	.txGpio = { Gpio::_ChA, 9,  Gpio::_Alt, 7, 0 },                       \
	.rxGpio = { Gpio::_ChA, 10, Gpio::_Alt, 7, 0 },                       \
	.deGpio = { 0, 0, 0, 0, 0 },                                          \
                                                                          \
	.txDma = { Dma::_Group1, Dma::_Stream3, 42, NULL, false },            \
	.rxDma = { Dma::_Group1, Dma::_Stream2, 41, NULL, true  },            \
}


//********************************SpiFlash********************************//
#define SPI_FLASH_CONFIG                                                  \
{                                                                         \
	.spiCh    = Spi::_Spi5,                                               \
                                                                          \
	.sckGpio  = { Gpio::_ChF, 7,  Gpio::_Alt,    5, 0 },                  \
	.misoGpio = { Gpio::_ChF, 8,  Gpio::_Alt,    5, 0 },                  \
	.mosiGpio = { Gpio::_ChF, 9,  Gpio::_Alt,    5, 0 },                  \
	.csGpio   = { Gpio::_ChF, 6,  Gpio::_Output, 0, 0 },                  \
	.wpGpio   = { 0, 0, 0, 0, 0 },                                        \
}


//********************************SDMMC***********************************//
#define SDMMC_CONFIG                                                      \
{                                                                         \
	.d0Gpio  = { Gpio::_ChC, 8,  Gpio::_Alt,  12, 0 },                    \
	.d1Gpio  = { Gpio::_ChC, 9,  Gpio::_Alt,  12, 0 },                    \
	.d2Gpio  = { Gpio::_ChC, 10, Gpio::_Alt,  12, 0 },                    \
	.d3Gpio  = { Gpio::_ChC, 11, Gpio::_Alt,  12, 0 },                    \
	.ckGpio  = { Gpio::_ChC, 12, Gpio::_Alt,  12, 0 },                    \
	.cmdGpio = { Gpio::_ChD, 2,  Gpio::_Alt,  12, 0 },                    \
}


#endif // !__HW_STM32H743_CONFIG_H__
