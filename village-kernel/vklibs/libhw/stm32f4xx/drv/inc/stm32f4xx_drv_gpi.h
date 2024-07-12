//###########################################################################
// stm32f4xx_drv_gpi.h
// Hardware layer that manages a single GPIO input
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GPI_H__
#define __GPI_H__

#include "stm32f4xx_drv.h"
#include "stm32f4xx_drv_gpio.h"


/// @brief Gpi
class Gpi : public Gpio
{
private:
	volatile uint32_t* dataReg;

public:
	//Methods
	Gpi();
	void Initialize(GpioChannel channel, uint16_t pin);
	void ConfigPullUpDown(GpioInputType pullMode);

	///Reads the value of the pin
	inline uint32_t Read() { return (*dataReg >> pinNum) & 0x1; }

	///Slightly more efficient than Read() but a logic high read may be any non-zero value
	inline uint32_t ReadRaw() { return *dataReg & bitMask;}
};

#endif //!__GPI_H__
