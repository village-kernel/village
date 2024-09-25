//###########################################################################
// Usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Usart.h"


/// @brief Constructor
Usart::Usart()
	: base(__null),
	channel(_Usart1)
{
}


/// @brief Initializes the serial module
/// @param channel 
void Usart::Initialize(Channel channel)
{
	//Get uart channel
	this->channel = channel;

	//assign the base pointer and enable the peripheral clock
	//also configure clock source to SYSCLK
	if (_Usart1 == channel)
	{
		RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
		RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		base = USART1;
	}
	else if (_Usart2 == channel)
	{
		RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
		RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;

		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		base = USART2;
	}
	else if (_Usart3 == channel)
	{
		RCC->APB1RSTR |= RCC_APB1RSTR_USART3RST;
		RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
		
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		base = USART3;
	}

	//Enable Receiver and Transmitter
	base->CR1 |= USART_CR1_RE_Msk | USART_CR1_TE_Msk;
}


/// @brief Configures basic port settings
/// @param dataBits 
/// @param parity 
/// @param stopBits 
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


/// @brief Sets the baud rate of the serial bus
///        baudRate indicates the desired baudRate
///        over8 indicates the whether oversampling by 8 will be used (otherwise oversampling of 16)
/// @param baudRate 
/// @param over8 
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


/// @brief Configure RS485 driver enable mode
/// @param usingDEM 
/// @param polarity 
void Usart::ConfigDriverEnableMode(bool usingDEM, bool polarity)
{
	//unsupport
}


/// @brief Configure receiver timeout
/// @param enable 
/// @param rto 
/// @param blen 
void Usart::ConfigReceiverTimeout(bool enable, uint32_t rto, uint8_t blen)
{
	//unsupport
}


/// @brief Enables or disables DMA transmitter / DMA receiver
/// @param dmaTxEnable 
/// @param dmaRxEnable 
void Usart::ConfigDma(bool dmaTxEnable, bool dmaRxEnable)
{
	if (dmaTxEnable) base->CR3 |= USART_CR3_DMAT;
	else base->CR3 &= ~USART_CR3_DMAT;

	if (dmaRxEnable) base->CR3 |= USART_CR3_DMAR;
	else base->CR3 &= ~USART_CR3_DMAR;
}


/// @brief Write data to usart
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Usart::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	uint16_t loop = size;

	data += offset;

	while (loop)
	{
		if (IsTxRegisterEmpty())
		{
			base->DR = *data++;
			loop--;
		}
	}

	return size;
}


/// @brief Read data from usart
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Usart::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	uint32_t length = 0;

	data += offset;

	while (IsReadDataRegNotEmpty())
	{
		*data++ = base->DR;
		if (++length >= size) break;
	}

	return length;
}


/// @brief Check error
void Usart::CheckError()
{
	if (base->SR & (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE))
	{
		base->SR = (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE);
	}
}
