//###########################################################################
// vk_drv_gpio.cpp
// Hardware Layer class that manages a single GPIO pin
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_gpio.h"

/// @brief Constructor
Gpio::Gpio()
    : GPIOx(GPIOA),
    GPIO_PIN_x(LL_GPIO_PIN_0)
{
}


/// @brief Initializes the internal members for the GPIO pin object.
///        does not actually perform any configuration
/// @param config
void Gpio::Initialize(Config config)
{
    // Set GPIOx based on config
    switch (config.ch)
    {
        case _ChA: GPIOx = GPIOA; break;
        case _ChB: GPIOx = GPIOB; break;
        case _ChC: GPIOx = GPIOC; break;
        case _ChD: GPIOx = GPIOD; break;
        case _ChE: GPIOx = GPIOE; break;
        case _ChF: GPIOx = GPIOF; break;
        case _ChG: GPIOx = GPIOG; break;
        case _ChH: GPIOx = GPIOH; break;
        case _ChI: GPIOx = GPIOI; break;
        case _ChJ: GPIOx = GPIOJ; break;
        case _ChK: GPIOx = GPIOK; break;
        // Default to GPIOA if invalid channel
        default: GPIOx = GPIOA; break;
    }

    // Set GPIO_PIN_x based on config
    GPIO_PIN_x = (0x1u << config.pin);

    // Enable the peripheral clock for the corresponding port
    switch (config.ch)
    {
        case _ChA: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA); break;
        case _ChB: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB); break;
        case _ChC: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC); break;
        case _ChD: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD); break;
        case _ChE: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE); break;
        case _ChF: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF); break;
        case _ChG: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG); break;
        case _ChH: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH); break;
        case _ChI: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI); break;
        case _ChJ: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOJ); break;
        case _ChK: LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOK); break;
    }

    // Set the correct mode
    ConfigMode((GpioMode)config.mode);

    // Set the output type
    if (_Output == config.mode || _Altera == config.mode)
        ConfigOutputType(_PushPull);
    
    // Set the pull type
    if (_Input == config.mode || _Altera == config.mode)
        ConfigPullType(_PullUp);

    // Set the correct value
    if (_Altera == config.mode)
        ConfigAltFunc((GpioAlternate)config.altfun);
    else if (_Output == config.mode)
        Write((GpioState)config.value);

    // Set the correct speed
    ConfigSpeed(_SuperSpeed);
}


/// @brief Sets the mode of the GPIO pin.
/// @param mode 
void Gpio::ConfigMode(GpioMode mode)
{
    LL_GPIO_SetPinMode(GPIOx, GPIO_PIN_x, mode);
}


/// @brief Configures internal pull up/down resistors
/// @param pullType 
void Gpio::ConfigPullType(GpioPullType pullType)
{
    LL_GPIO_SetPinPull(GPIOx, GPIO_PIN_x, pullType);
}


/// @brief Configures push-pull or open-drain for output pins
/// @param outputType 
void Gpio::ConfigOutputType(GpioOutType outputType)
{
    LL_GPIO_SetPinOutputType(GPIOx, GPIO_PIN_x, outputType);
}


/// @brief Configures the output speed
/// @param speed 
void Gpio::ConfigSpeed(GpioSpeed speed)
{
    LL_GPIO_SetPinSpeed(GPIOx, GPIO_PIN_x, speed);
}


/// @brief Sets the alternate function of the pin when pin mode is configured 
///        as alternate mode. For AF0 pass in 0, for AF1 pass in 1 etc.
/// @param altMode 
void Gpio::ConfigAltFunc(GpioAlternate altMode)
{
    if (GPIO_PIN_x & 0x00FF) // Lower 8 pins (0-7)
    {
        LL_GPIO_SetAFPin_0_7(GPIOx, GPIO_PIN_x, altMode);
    }
    else // Upper 8 pins (8-15)
    {
        LL_GPIO_SetAFPin_8_15(GPIOx, GPIO_PIN_x, altMode);
    }
}
