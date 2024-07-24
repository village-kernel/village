//###########################################################################
// stm32h7xx_drv_sdio.h
// Hardware Layer class that manages a single sdio module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SDIO_H__
#define __SDIO_H__

#include "stm32h7xx_drv.h"
#include "stm32h7xx_drv_gpio.h"


/// @brief Sdio
class Sdio
{
public:
	//Structures
	struct Config
	{
		Gpio::GpioChannel d0Ch;
		Gpio::GpioChannel d1Ch;
		Gpio::GpioChannel d2Ch;
		Gpio::GpioChannel d3Ch;
		Gpio::GpioChannel ckCh;
		Gpio::GpioChannel cmdCh;
		uint16_t d0Pin;
		uint16_t d1Pin;
		uint16_t d2Pin;
		uint16_t d3Pin;
		uint16_t ckPin;
		uint16_t cmdPin;
		uint8_t d0AltNum;
		uint8_t d1AltNum;
		uint8_t d2AltNum;
		uint8_t d3AltNum;
		uint8_t ckAltNum;
		uint8_t cmdAltNum;
	};
public:
	//Members
	SD_HandleTypeDef hsd1;

	//Methods
	void PinConfig(Config config);
public:
	//Methods
	void Initialize(Config config);
	int Write(uint8_t* data, uint32_t count = 0, uint32_t blk = 0);
	int Read(uint8_t* data, uint32_t count = 0, uint32_t blk = 0);
};

#endif // !__SDIO_H__
