//###########################################################################
// stm32f4xx_drv_fsmc.h
// Hardware layer class that manages FSMC module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FSMC_H__
#define __FSMC_H__

#include "stm32f4xx_drv_gpio.h"


/// @brief FSMC
class Fsmc
{
public:
	struct Config
	{
		Gpio::GpioChannel csCh;
		uint16_t csPin;
		Gpio::GpioChannel rsCh;
		uint16_t rsPin;
		Gpio::GpioChannel wrCh;
		uint16_t wrPin;
		Gpio::GpioChannel rdCh;
		uint16_t rdPin;
		Gpio::GpioChannel db0Ch;
		uint16_t db0Pin;
		Gpio::GpioChannel db1Ch;
		uint16_t db1Pin;
		Gpio::GpioChannel db2Ch;
		uint16_t db2Pin;
		Gpio::GpioChannel db3Ch;
		uint16_t db3Pin;
		Gpio::GpioChannel db4Ch;
		uint16_t db4Pin;
		Gpio::GpioChannel db5Ch;
		uint16_t db5Pin;
		Gpio::GpioChannel db6Ch;
		uint16_t db6Pin;
		Gpio::GpioChannel db7Ch;
		uint16_t db7Pin;
		Gpio::GpioChannel db8Ch;
		uint16_t db8Pin;
		Gpio::GpioChannel db9Ch;
		uint16_t db9Pin;
		Gpio::GpioChannel db10Ch;
		uint16_t db10Pin;
		Gpio::GpioChannel db11Ch;
		uint16_t db11Pin;
		Gpio::GpioChannel db12Ch;
		uint16_t db12Pin;
		Gpio::GpioChannel db13Ch;
		uint16_t db13Pin;
		Gpio::GpioChannel db14Ch;
		uint16_t db14Pin;
		Gpio::GpioChannel db15Ch;
		uint16_t db15Pin;
	};
private:
	static const uint8_t pin_alt_num = 12;

	//Methods
	void PinConfig(Config config);
public:
	//Methods
	void Initialize(Config config);
};

#endif //!__FSMC_H__
