//###########################################################################
// stm32f4xx_drv_usart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx_drv.h"
#include "stm32f4xx_drv_gpio.h"


/// @brief Usart
class Usart
{	
public:
	//Enumerations
	enum DataBits
	{
		_8Bits = 0,
		_9Bits = 1,
	};

	enum Parity
	{
		_NoParity = 0,
		_Parity = 1,
	};

	enum StopBits
	{
		_1Stop = 0b00,
		_HalfStop = 0b01,
		_2Stop = 0b10,
		_1AndHalfStop = 0b11,
	};

	//Structures
	struct PinConfig
	{
		Gpio::GpioChannel ch;
		uint16_t pin;
		uint16_t alt;
	};	
private:
	//Members
	volatile USART_TypeDef* base;
	volatile uint16_t channel;
public:
	//Methods
	Usart();
	void Initialize(uint16_t channel);
	void ConfigPin(PinConfig config);
	void ConfigPortSettings(DataBits dataBits, Parity parity, StopBits stopBits);
	void ConfigDriverEnableMode(bool usingDEM = true, bool polarity = false);
	void ConfigReceiverTimeout(bool enable, uint32_t rto = 0, uint8_t blen = 0);
	void ConfigDma(bool dmaTxEnable = true, bool dmaRxEnable = true);
	void SetBaudRate(uint32_t baudRate, bool over8 = false);
	void CheckError();
	int Write(uint8_t* data, uint32_t size, uint32_t offset);
	int Read(uint8_t* data, uint32_t size, uint32_t offset);

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

	///Clears the receiver timeout flag, not support
	inline void ClearReceiverTimeoutFlag() {  }

	///Check if the send register is empty
	inline bool IsTxRegisterEmpty() { return bool(base->SR & USART_SR_TXE_Msk); }

	///Check if the read date register not empty
	inline bool IsReadDataRegNotEmpty() { return bool(base->SR & USART_SR_RXNE_Msk); }

	///Check if receiver timeout, not support
	inline bool IsReceiverTimeout() { return false; }
};

#endif //!__USART_H__
