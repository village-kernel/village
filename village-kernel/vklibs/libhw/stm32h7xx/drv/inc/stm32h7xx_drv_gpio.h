//###########################################################################
// stm32h7xx_drv_gpio.h
// Hardware Layer class that manages a single GPIO pin
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32h7xx_drv.h"


/// @brief Gpio
class Gpio
{
protected:
	//Static Constants
	static const uint32_t baseRegOffset = 0x400;
	static const uint16_t maxFourBitPin = 8;

	//Members
	GPIO_TypeDef* baseReg;
	uint32_t bitMask;
	uint16_t pinNum;
public:
	//Enumerations
	enum GpioChannel
	{
		_ChA = 0,
		_ChB = 1,
		_ChC = 2,
		_ChD = 3,
		_ChE = 4,
		_ChF = 5,
		_ChG = 6,
		_ChH = 7,
		_ChI = 8,
		_ChJ = 9,
		_ChK = 10,
	};
	
	enum GpioMode
	{
		_Input  = 0b00,
		_Output = 0b01,
		_Alt    = 0b10,
		_Analog = 0b11,
	};

	enum GpioState
	{
		_Low = 0,
		_High = 1,
	};

	enum GpioOutType
	{
		_PushPull = 0,
		_OpenDrain = 1,
	};

	enum GpioInputType
	{
		_NoPull   = 0b00,
		_PullUp   = 0b01,
		_PullDown = 0b10,
	};

	enum GpioSpeed
	{
		_LowSpeed  = 0b00,
		_MedSpeed  = 0b01,
		_HighSpeed = 0b10,
		_SuperHighSpeed = 0b11,
	};

	struct Config
	{
		uint16_t ch;
		uint16_t pin;
		uint16_t mode;
		uint16_t altfun;
		uint16_t value;
	};
private:
	///Returns the mask used for register manipulation
	inline uint32_t BitMask() { return bitMask; }

	///Returns the mask used for double bit register manipulation
	inline uint32_t DoubleBitMask() { return 0b11 << (pinNum * 2); }
public:
	//Methods
	Gpio();
	void Initialize(Config config);
	void ConfigMode(GpioMode mode);
	void ConfigInputType(GpioInputType inputType);
	void ConfigOutputType(GpioOutType outputType);
	void ConfigSpeed(GpioSpeed speed);
	void ConfigAltFunc(uint8_t altMode);
	
	///Reads the value of the pin
	inline uint32_t Read() { return (baseReg->IDR >> pinNum) & 0x1; }

	///Slightly more efficient than Read() but a logic high read may be any non-zero value
	inline uint32_t ReadRaw() { return baseReg->IDR & bitMask; }

	///Drives the pin high
	inline void Set() { baseReg->BSRR = bitMask; }

	///Drives the pin low
	inline void Clear() { baseReg->BSRR = (bitMask << 16); }

	///Toggles the pin value
	inline void Toggle() { if (_Low == GetOutputState()) Set(); else Clear(); }

	///Writes a specified state into the pin
	inline void Write(GpioState state) { if (_Low == state) Clear(); else Set(); }

	///Gets the current input state
	inline GpioState GetInputState() { return (GpioState)((baseReg->IDR >> pinNum) & 0x1); }

	///Gets the current output state
	inline GpioState GetOutputState() { return (GpioState)((baseReg->ODR >> pinNum) & 0x1); }
};

#endif // !__GPIO_H__
