//###########################################################################
// Usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Usart.h"


///Default Constructor
Usart::Usart()
	: base(__null),
	channel(0)
{
}


///Initializes the serial module
void Usart::Initialize(uint16_t channel)
{
	//Get uart channel
	this->channel = channel;

	//assign the base pointer and enable the peripheral clock
	//also configure clock source to SYSCLK
	if (1 == channel)
	{
		RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
		RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		base = USART1;
	}
	else if (2 == channel)
	{
		RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
		RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;

		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		base = USART2;
	}
	else if (3 == channel)
	{
		RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;
		RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
		
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		base = USART3;
	}

	//Enable Receiver and Transmitter
	base->CR1 |= USART_CR1_RE_Msk | USART_CR1_TE_Msk;
}


///Configures usart pins
void Usart::ConfigPin(PinConfig config)
{
	Gpio usartPin;
	usartPin.Initialize(config.ch, config.pin);
	usartPin.ConfigAltFunc(config.alt);
	usartPin.ConfigMode(Gpio::_Alt);
	usartPin.ConfigOutputType(Gpio::_PushPull);
	usartPin.ConfigInputType(Gpio::_NoPull);
	usartPin.ConfigSpeed(Gpio::_HighSpeed);
}


///Configures basic port settings
void Usart::ConfigPortSettings(DataBits dataBits, Parity parity, StopBits stopBits)
{
	//Configure word size
	if (_9Bits == dataBits)
	{
		base->CR1 |= USART_CR1_M;
	}
	else if (_8Bits == dataBits)
	{
		base->CR1 &= ~USART_CR1_M;
	}

	//Configure parity
	if (_Parity == parity)
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
	//Calculate the pclk1 frequency
	uint32_t PCLKFreq = 0;

	if (1 == channel || 6 == channel)
	{
		uint32_t tmp = APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos];
		PCLKFreq = SystemCoreClock >> tmp;
	}
	else
	{
		uint32_t tmp = APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos];
		PCLKFreq = SystemCoreClock >> tmp;
	}

	//Calculate the baudrate of 8x Oversampling
	if (over8)
	{
		base->CR1 |= USART_CR1_OVER8;
		base->BRR = (PCLKFreq * 2 + baudRate / 2) / baudRate;
	}
	//Calculate the baudrate of 16x Oversampling 
	else
	{
		base->CR1 &= ~USART_CR1_OVER8;
		base->BRR = (PCLKFreq + baudRate / 2) / baudRate;
	}
}


///Configure RS485 driver enable mode
void Usart::ConfigDriverEnableMode(bool usingDEM, bool polarity)
{
	//unsupport
}


///Configure receiver timeout
void Usart::ConfigReceiverTimeout(bool enable, uint32_t rto, uint8_t blen)
{
	//unsupport
}


///Enables or disables DMA transmitter / DMA receiver
void Usart::ConfigDma(bool dmaTxEnable, bool dmaRxEnable)
{
	if (dmaTxEnable) base->CR3 |= USART_CR3_DMAT;
	else base->CR3 &= ~USART_CR3_DMAT;

	if (dmaRxEnable) base->CR3 |= USART_CR3_DMAR;
	else base->CR3 &= ~USART_CR3_DMAR;
}


///Write data to usart
int Usart::Write(uint8_t* txData, uint16_t length)
{
	while (length)
	{
		if (IsTxRegisterEmpty())
		{
			base->DR = *txData++;
			length--;
		}
	}

	return 0;
}


///Read data from usart
int Usart::Read(uint8_t* rxData, uint16_t length)
{
	while (length)
	{
		if (IsReadDataRegNotEmpty())
		{
			*rxData++ = base->DR;
			length--;
		}
	}

	return 0;
}


///Check error
void Usart::CheckError()
{
	if (base->SR & (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE))
	{
		base->SR = (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE);
	}
}
