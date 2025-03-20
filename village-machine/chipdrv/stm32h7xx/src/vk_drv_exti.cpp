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
	extiLine = line;
	if (31 >= line)
	{
		bitMask = 1 << extiLine;
		pendingReg = &(EXTI_D1->PR1);
	}
	else
	{
		bitMask = 1 << (extiLine - 32);
		pendingReg = &(EXTI_D1->PR2);
	}

	//Enable sys cfg clock
	RCC->APB4ENR |= RCC_APB4ENR_SYSCFGEN;
}


/// @brief Select between event or interrupt mode
/// @param mode 
void Exti::ConfigMode(ExtIntMode mode)
{
	if (31 >= extiLine)
	{
		if (_Interrupt == mode)
		{
			EXTI_D1->IMR1 |= bitMask;
			EXTI_D1->EMR1 &= ~bitMask;
		}
		else
		{
			EXTI_D1->IMR1 &= ~bitMask;
			EXTI_D1->EMR1 |= bitMask;
		}
	}
	else
	{
		if (_Interrupt == mode)
		{
			EXTI_D1->IMR2 |= bitMask;
			EXTI_D1->EMR2 &= ~bitMask;
		}
		else
		{
			EXTI_D1->IMR2 &= ~bitMask;
			EXTI_D1->EMR2 |= bitMask;
		}
	}
}


/// @brief Selects external interrupt trigger edge
/// @param edge 
void Exti::ConfigTriggerEdge(ExtIntEdge edge)
{
	if (31 >= extiLine)
	{
		if (_Rising == edge)
		{
			EXTI->RTSR1 |= bitMask;
			EXTI->FTSR1 &= ~bitMask;
		}
		else if (_Falling == edge)
		{
			EXTI->RTSR1 &= ~bitMask;
			EXTI->FTSR1 |= bitMask;
		}
		else
		{
			EXTI->RTSR1 |= bitMask;
			EXTI->FTSR1 |= bitMask;
		}
	}
	else
	{
		if (_Rising == edge)
		{
			EXTI->RTSR2 |= bitMask;
			EXTI->FTSR2 &= ~bitMask;
		}
		else if (_Falling == edge)
		{
			EXTI->RTSR2 &= ~bitMask;
			EXTI->FTSR2 |= bitMask;
		}
		else
		{
			EXTI->RTSR2 |= bitMask;
			EXTI->FTSR2 |= bitMask;
		}
	}
}


/// @brief Software Generated Interrupt
///        This bit is cleared by clearing the corresponding bit in the EXTI_PR register (by
///        writing a ‘1’ into the bit).
void Exti::SoftInt()
{
	if (31 >= extiLine)
	{
		EXTI->SWIER1 |= bitMask;
	}
	else
	{
		EXTI->SWIER2 |= bitMask;
	}
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
	nvic.DisableInterrupt();
}
