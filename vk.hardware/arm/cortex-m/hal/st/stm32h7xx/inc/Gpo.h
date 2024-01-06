//###########################################################################
// Gpo.h
// Hardware layer that manages a single GPIO output pin
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GPO_H__
#define __GPO_H__

#include "HalHeaders.h"
#include "Gpio.h"

///Gpo
class Gpo : public Gpio
{
private:
	volatile uint32_t* setReg;
	volatile uint32_t* clearReg;

public:
	//Methods
	Gpo();
	void Initialize(GpioChannel channel, uint16_t pin, GpioState initState);
	void ConfigType(GpioOutType outType);
	void Write(GpioState state);
	void Toggle();

	///Gets the current output state
	inline GpioState GetOutputState() { return (GpioState)((baseReg->ODR >> pinNum) & 0x1); }

	///Gets the current input state
	inline GpioState GetInputState() { return (GpioState)((baseReg->IDR >> pinNum) & 0x1); }

	///Drives the pin high
	inline void Set() { *setReg = bitMask; }

	///Drives the pin low
	inline void Clear() { *clearReg = (bitMask << 16); }
};

#endif /* __GPO_H__ */
