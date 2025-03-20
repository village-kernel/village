//###########################################################################
// vk_drv_exti.cpp
// Hardware Layer class that manages external interrupts
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_drv_exti.h"
#include "vk_drv_nvic.h"


/// @brief Constructor
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
/// @param edge 
void Exti::ConfigTriggerEdge(ExtiEdge edge)
{
    if (_Rising == edge)
    {
        EXTI->RTSR |= bitMask;
        EXTI->FTSR &= ~bitMask;
    }
    else if (_Falling == edge)
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
void Exti::ConfigExtPin(Gpio::Config pinCfg)
{
    int nTemp = 0;
    int nGroup = 0;
    uint32_t pinCh = pinCfg.ch;
    uint32_t pinNum = pinCfg.pin;

    if (3 >= pinNum)
    {
        nTemp = pinNum;
        nGroup = 0;
    }
    else if (7 >= pinNum)
    {
        nTemp = pinNum - 4;
        nGroup = 1;
    }
    else if (11 >= pinNum)
    {
        nTemp = pinNum - 8;
        nGroup = 2;
    }
    else
    {
        nTemp = pinNum - 12;
        nGroup = 3;
    }

    SYSCFG->EXTICR[nGroup] = (SYSCFG->EXTICR[nGroup] & ~(0xf << (nTemp * 4))) | (pinCh << (nTemp * 4));
}


/// @brief Enable ext interrupt
/// @param enable 
void Exti::EnableExtInterrupt(uint16_t irq)
{
	Nvic nvic;
    nvic.Initialize((IRQn_Type)irq);
	nvic.EnableInterrupt();
}


/// @brief Disable ext interrupt
/// @param enable 
void Exti::DisableExtInterrupt(uint16_t irq)
{
	Nvic nvic;
    nvic.Initialize((IRQn_Type)irq);
	nvic.DisbleInterrupt();
}
