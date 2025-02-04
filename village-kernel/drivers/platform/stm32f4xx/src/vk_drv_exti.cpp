//###########################################################################
// vk_drv_exti.cpp
// Hardware Layer class that manages external interrupts
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_exti.h"
#include "vk_drv_nvic.h"


///Constructor
Exti::Exti()
    :extiLine(0),
    bitMask(0),
    pendingReg(NULL)
{
}


/// @brief Selects the interrupt line
/// @param line 
void Exti::Initialize(uint8_t line)
{
    //config regs
    extiLine = line;
    bitMask  = 1 << extiLine;
    pendingReg = &(EXTI->PR);

    //Enable sys cfg clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}


/// @brief Select between event or interrupt mode
/// @param mode 
void Exti::ConfigMode(ExtiMode mode)
{
    if (_Interrupt == mode)
    {
        EXTI->IMR |= bitMask;
        EXTI->EMR &= ~bitMask;
    }
    else
    {
        EXTI->IMR &= ~bitMask;
        EXTI->EMR |= bitMask;
    }
}


/// @brief Selects external interrupt trigger edge
/// @param trigger 
void Exti::ConfigTriggerEdge(ExtiEdge trigger)
{
    if (_Rising == trigger)
    {
        EXTI->RTSR |= bitMask;
        EXTI->FTSR &= ~bitMask;
    }
    else if (_Falling == trigger)
    {
        EXTI->RTSR &= ~bitMask;
        EXTI->FTSR |= bitMask;
    }
    else
    {
        EXTI->RTSR |= bitMask;
        EXTI->FTSR |= bitMask;
    }
}


/// @brief Software Generated Interrupt
///        This bit is cleared by clearing the corresponding bit in the EXTI_PR register (by
///        writing a ‘1’ into the bit).
void Exti::SoftInt()
{
    EXTI->SWIER |= bitMask;
}


/// @brief Configures the Gpi pin that triggers the interrupt
/// @param ch 
/// @param pin 
void Exti::ConfigExtPin(Gpio::GpioChannel ch, uint8_t pin)
{
    int nTemp = 0;
    int nGroup = 0;

    if (3 >= pin)
    {
        nTemp = pin;
        nGroup = 0;
    }
    else if (7 >= pin)
    {
        nTemp = pin - 4;
        nGroup = 1;
    }
    else if (11 >= pin)
    {
        nTemp = pin - 8;
        nGroup = 2;
    }
    else
    {
        nTemp = pin - 12;
        nGroup = 3;
    }

    SYSCFG->EXTICR[nGroup] = (SYSCFG->EXTICR[nGroup] & ~(0xf << (nTemp * 4))) | (ch << (nTemp * 4));
}


/// @brief Enable ext interrupt
/// @param enable 
void Exti::EnableInterrupt(bool enable)
{
    Nvic nvic;
    if (0 == extiLine)
        nvic.Initialize(EXTI0_IRQn);
    else if (1 == extiLine)
        nvic.Initialize(EXTI1_IRQn);
    else if (2 == extiLine)
        nvic.Initialize(EXTI2_IRQn);
    else if (3 == extiLine)
        nvic.Initialize(EXTI3_IRQn);
    else if (4 == extiLine)
        nvic.Initialize(EXTI4_IRQn);
    else if (extiLine >= 5 && extiLine <= 9)
        nvic.Initialize(EXTI9_5_IRQn);
    else if (extiLine >= 10 && extiLine <= 15)
        nvic.Initialize(EXTI15_10_IRQn);
    nvic.ConfigPriorityGroupSetting(Nvic::_PriorityGroup3);
    nvic.SetPriority(0, 0);
    if (enable) nvic.EnableInterrupt();
    else nvic.DisableInterrupt();
}
