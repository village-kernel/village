//###########################################################################
// stm32h7xx_drv_gpio.cpp
// Hardware Layer class that manages a single GPIO pin
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stm32h7xx_drv_gpio.h"


/// @brief Constructor
Gpio::Gpio()
	: baseReg((GPIO_TypeDef *)GPIOA_BASE),
	bitMask(0),
	pinNum(0)
{
}


/// @brief Initializes the internal members for the GPIO pin object.
///        does not actually perform any configuration
/// @param config
void Gpio::Initialize(Config config)
{
	baseReg = (GPIO_TypeDef *)(GPIOA_BASE + (config.ch * baseRegOffset));
	pinNum = config.pin;
	bitMask = 0x1 << pinNum;

	//Enable the peripheral clock for the corresponding port
	uint32_t clkEnaMask = RCC_AHB4ENR_GPIOAEN_Msk << config.ch;
	RCC->AHB4ENR |= clkEnaMask;

	//Set the correct mode
	ConfigMode((GpioMode)config.mode);

	//Set the correct type
	if (_Output == config.mode)
		ConfigOutputType(_PushPull);
	else if (_Input == config.mode)
		ConfigInputType(_PullUp);

	//Set the correct value
	if (_Altera == config.mode)
		ConfigAltFunc(config.altfun);
	else if (_Output == config.mode)
		Write((GpioState)config.value);
}


/// @brief Sets the mode of the GPIO pin.
/// @param mode 
void Gpio::ConfigMode(GpioMode mode)
{
	baseReg->MODER = (baseReg->MODER & ~(DoubleBitMask())) | (mode << (pinNum * 2));
}


/// @brief Configures internal pull up/down resistors
/// @param inputType 
void Gpio::ConfigInputType(GpioInputType inputType)
{
	baseReg->PUPDR = (baseReg->PUPDR & ~(DoubleBitMask())) | (inputType << (pinNum * 2));
}


/// @brief Configures push-pull or open-drain for output pins
/// @param outputType 
void Gpio::ConfigOutputType(GpioOutType outputType)
{
	baseReg->OTYPER = (baseReg->OTYPER & ~(BitMask())) | (outputType << pinNum);
}


/// @brief Configures the output speed
/// @param speed 
void Gpio::ConfigSpeed(GpioSpeed speed)
{
	baseReg->OSPEEDR = (baseReg->OSPEEDR & ~(DoubleBitMask())) | (speed << (pinNum * 2));
}


/// @brief Sets the alternate function of the pin when pin mode is configured 
///        as alternate mode. For AF0 pass in 0, for AF1 pass in 1 etc.
/// @param altfun 
void Gpio::ConfigAltFunc(uint8_t altfun)
{
	if (pinNum < maxFourBitPin)
	{
		uint32_t shift = pinNum * 4;
		uint32_t mask = ~(0xF << shift);
		baseReg->AFR[0] = (baseReg->AFR[0] & mask) | (altfun << shift);
	}
	else
	{
		uint32_t shift = (pinNum - maxFourBitPin) * 4;
		uint32_t mask = ~(0xF << shift);
		baseReg->AFR[1] = (baseReg->AFR[1] & mask) | (altfun << shift);
	}
}
