//###########################################################################
// vk_drv_exti.h
// Hardware Layer class that manages external interrupts
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_EXTI_H__
#define __VK_DRV_EXTI_H__

#include "stm32f4xx.h"
#include "vk_drv_gpio.h"


/// @brief Exti
class Exti
{
public:
    //Enumerations
    enum ExtiMode
    {
        _Interrupt = 0,
        _Event = 1,
    };

    enum ExtiEdge
    {
        _Rising = 0,
        _Falling = 1,
        _BothEdge = 2,
    };

private:
    //Members
    volatile uint32_t  extiLine;
    volatile uint32_t  bitMask;
    volatile uint32_t* pendingReg;
public:
    //Methods
    Exti();
    void Initialize(uint8_t line);
    void ConfigMode(ExtiMode mode);
    void ConfigTriggerEdge(ExtiEdge trigger);
    void ConfigExtPin(Gpio::GpioChannel ch, uint8_t pin);
    void EnableInterrupt(bool enable = true);
    void SoftInt();

    ///Checks whether an external interrupt event has occured
    inline bool Check() { return (bool)*pendingReg & bitMask; };

    ///Clears the external interrupt event flag
    inline void Clear() { *pendingReg |= bitMask; };
};

#endif //!__VK_DRV_EXTI_H__
