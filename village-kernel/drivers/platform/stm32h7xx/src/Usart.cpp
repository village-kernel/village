//###########################################################################
// Usart.cpp
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Usart.h"


/// @brief Constructor
Usart::Usart()
	: base(NULL)
{
}


/// @brief Initializes the serial module
/// @param channel 
void Usart::Initialize(Channel channel)
{
	//Enable the peripheral clock and assign the base pointer
	if (_Usart1 == channel)
	{
		RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
		RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
		
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		base = USART1;
	}
	else if (_Usart2 == channel)
	{
		RCC->APB1LRSTR |= RCC_APB1LRSTR_USART2RST;
		RCC->APB1LRSTR &= ~RCC_APB1LRSTR_USART2RST;

		RCC->APB1LENR |= RCC_APB1LENR_USART2EN;
		base = USART2; 
	}
	else if (_Usart3 == channel)
	{
		RCC->APB1LRSTR |= RCC_APB1LRSTR_USART3RST;
		RCC->APB1LRSTR &= ~RCC_APB1LRSTR_USART3RST;

		RCC->APB1LENR |= RCC_APB1LENR_USART3EN;
		base = USART3;
	}
	else if (_Usart4 == channel)
	{
		RCC->APB1LRSTR |= RCC_APB1LRSTR_UART4RST;
		RCC->APB1LRSTR &= ~RCC_APB1LRSTR_UART4RST;

		RCC->APB1LENR |= RCC_APB1LENR_UART4EN;
		base = UART4;
	}
	else if (_Usart5 == channel)
	{
		RCC->APB1LRSTR |= RCC_APB1LRSTR_UART5RST;
		RCC->APB1LRSTR &= ~RCC_APB1LRSTR_UART5RST;

		RCC->APB1LENR |= RCC_APB1LENR_UART5EN;
		base = UART5;
	}

	//Enable FIFO mode
	base->CR1 |= USART_CR1_FIFOEN_Msk;

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
		base->CR1 |= USART_CR1_M0;
	}
	else if (_8Bits == dataBits)
	{
		base->CR1 &= ~USART_CR1_M0;
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
	if (0 != baudRate)
	{
		//Calculate the pclk1 frequency
		uint32_t tmp = (D1CorePrescTable[(RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) >> RCC_D2CFGR_D2PPRE1_Pos]) & 0x1FU;
		uint32_t PCLK1Freq = SystemD2Clock >> tmp;

		//Calculate the baudrate of 8x Oversampling
		if (over8)
		{
			base->CR1 |= USART_CR1_OVER8;
			base->BRR = (PCLK1Freq * 2 + baudRate / 2) / baudRate;
		}
		//Calculate the baudrate of 16x Oversampling 
		else
		{
			base->CR1 &= ~USART_CR1_OVER8;
			base->BRR = (PCLK1Freq + baudRate / 2) / baudRate;
		}
	}
	else
	{
		//Measurement of the start bit is used to detect the baud rate
		base->CR2 = (base->CR2 & ~USART_CR2_ABRMODE_Msk);

		//Auto baud rate enable
		base->CR2 |= USART_CR2_ABREN;
	}
}


/// @brief Configure RS485 driver enable mode
/// @param usingDEM 
/// @param polarity 
void Usart::ConfigDriverEnableMode(bool usingDEM, bool polarity)
{
	base->CR3 = (base->CR3 & ~USART_CR3_DEM_Msk) | ((usingDEM ? 1 : 0) << USART_CR3_DEM_Pos);
	base->CR3 = (base->CR3 & ~USART_CR3_DEP_Msk) | ((polarity ? 1 : 0) << USART_CR3_DEP_Pos);
}


/// @brief Configure receiver timeout
/// @param enable 
/// @param rto 
/// @param blen 
void Usart::ConfigReceiverTimeout(bool enable, uint32_t rto, uint8_t blen)
{
	base->CR2 = (base->CR2 & ~USART_CR2_RTOEN_Msk) | ((enable ? 1 : 0) << USART_CR2_RTOEN_Pos);
	base->RTOR = (base->RTOR & ~USART_RTOR_BLEN_Msk) | (blen << USART_RTOR_BLEN_Pos);
	base->RTOR = (base->RTOR & ~USART_RTOR_RTO_Msk) | (rto << USART_RTOR_RTO_Pos);
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
			base->TDR = *data++;
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
		*data++ = base->RDR;
		if (++length >= size) break;
	}

	return length;
}


/// @brief Check error
void Usart::CheckError()
{
	if (base->ISR & (USART_ISR_PE | USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE))
	{
		base->ICR = (USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF);
	}
}
