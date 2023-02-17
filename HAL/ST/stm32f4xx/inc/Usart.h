//###########################################################################
// Usart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USART_H__
#define __USART_H__

#include "HalHeaders.h"


///Usart
class Usart
{
private:

	//Members
	volatile USART_TypeDef* base;

public:
	//Enumerations
	enum UsartStopBits
	{
		_1Stop = 0b00,
		_HalfStop = 0b01,
		_2Stop = 0b10,
		_1AndHalfStop = 0b11,
	};

	//Methods
	Usart();
	void Initialize(uint16_t channel);
	void ConfigPortSettings(uint8_t dataBits, bool parity, UsartStopBits stopBits);
	void ConfigDma(bool dmaTxEnable, bool dmaRxEnable);
	void SetBaudRate(uint32_t baudRate, bool over8 = false);

	///Enables operation of the USART peripheral
	inline void Enable() { base->CR1 |= USART_CR1_UE; }

	///Disables operation of the USART peripheral
	inline void Disable() { base->CR1 &= ~USART_CR1_UE; }

	///Gets the address of the transmit data register
	inline uint32_t* GetTxAddr() { return (uint32_t*)&(base->DR); }

	///Gets the address of the receive data register
	inline uint32_t* GetRxAddr() { return (uint32_t*)&(base->DR); }

	///Checks for Framing Errors
	inline bool CheckFramingError() { return (base->SR & USART_SR_FE_Msk); }

	///Clears the Framing Error flag
	inline void ClearFramingError() { base->SR |= USART_SR_FE_Msk; }
};

#endif //!__USART_H__
