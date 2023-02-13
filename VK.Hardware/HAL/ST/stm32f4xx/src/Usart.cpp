//###########################################################################
// Usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Usart.h"


///Default Constructor
Usart::Usart()
	: base(__null)
{
}


///Initializes the serial module
void Usart::Initialize(uint16_t channel)
{
	//assign the base pointer and enable the peripheral clock
	//also configure clock source to SYSCLK
	if (1 == channel)
	{
		base = USART1;
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if (2 == channel)
	{
		base = USART2;
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	}
	else if (3 == channel)
	{
		base = USART3;
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}

	//Enable Receiver and Transmitter
	base->CR1 |= USART_CR1_RE_Msk | USART_CR1_TE_Msk;
}


///Configures basic port settings
void Usart::ConfigPortSettings(uint8_t dataBits, bool parity, UsartStopBits stopBits)
{
	//Configure word size
	if (9 == dataBits)
	{
		base->CR1 |= USART_CR1_M;
	}
	else if (8 == dataBits)
	{
		base->CR1 &= ~USART_CR1_M;
	}

	//Configure parity
	if (parity)
		base->CR1 |= USART_CR1_PCE;
	else
		base->CR1 &= ~USART_CR1_PCE;

	//Configure stop bits
	base->CR2 = (base->CR2 & ~USART_CR2_STOP_Msk) | (stopBits << USART_CR2_STOP_Pos);
}


///Sets the baud rate of the serial bus
///baudRate indicates the desired baudRate
///over8 indicates the whether oversampling by 8 will be used (otherwise oversampling of 16)
void Usart::SetBaudRate(uint32_t baudRate, bool over8)
{
	//8x Oversampling
	if (over8)
	{
		base->CR1 |= USART_CR1_OVER8;
		base->BRR = (SystemCoreClock * 2 + baudRate / 2) / baudRate;
	}
	//16x Oversampling 
	else
	{
		base->CR1 &= ~USART_CR1_OVER8;
		base->BRR = (SystemCoreClock + baudRate / 2) / baudRate;
	}
}


///Enables or disables DMA transmitter / DMA receiver
void Usart::ConfigDma(bool dmaTxEnable, bool dmaRxEnable)
{
	if (dmaTxEnable) base->CR3 |= USART_CR3_DMAT;
	else base->CR3 &= ~USART_CR3_DMAT;

	if (dmaRxEnable) base->CR3 |= USART_CR3_DMAR;
	else base->CR3 &= ~USART_CR3_DMAR;
}
