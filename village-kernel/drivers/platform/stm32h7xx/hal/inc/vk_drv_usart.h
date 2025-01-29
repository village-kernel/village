//###########################################################################
// vk_drv_usart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_USART_H__
#define __VK_DRV_USART_H__

#include "vk_hardware.h"
#include "vk_drv_gpio.h"


/// @brief Usart
class Usart
{
public:
	//Enumerations
	enum Channel
	{
		_Usart1 = 1,
		_Usart2 = 2,
		_Usart3 = 3,
		_Usart4 = 4,
		_Usart5 = 5,
	};

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

	enum InterruptType
	{
		_IdleInterrupt = 4,
		_RecDateRegNotEmpty,
		_TransComplete,
		_TransDataRegEmpty,
	};
private:
	//Static Constants
	static const uint8_t interruptSize = 5;

	//Members
	volatile USART_TypeDef* base;
public:
	//Methods
	Usart();
	void Initialize(Channel channel);
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

	///Configure interrupt
	inline void ConfigInterrupt(InterruptType type) { base->CR1 |= (1 << type); }

	///Gets the address of the transmit data register
	inline uint32_t* GetTxAddr() { return (uint32_t*)&(base->TDR); }

	///Gets the address of the receive data register
	inline uint32_t* GetRxAddr() { return (uint32_t*)&(base->RDR); }

	///Checks for Framing Errors
	inline bool CheckFramingError() { return (base->ISR & USART_ISR_FE_Msk); }

	///Clears the Framing Error flag
	inline void ClearFramingError() { base->ICR |= USART_ICR_FECF_Msk; }

	///Clears the trans complete flag
	inline void ClearTransCompleteFlag() { base->ICR |= USART_ICR_TCCF_Msk; }

	///Clears the trans data register empty flag
	inline void ClearTransDataRegEmptyFlag() { base->RQR |= USART_RQR_TXFRQ_Msk; }

	///Clears the read data register not empty flag
	inline void ClearReadDataRegNotEmptyFlag() { base->RQR |= USART_RQR_RXFRQ_Msk; }

	///Clears the idle line detected flag
	inline void ClearIdleLineDetectedFlag() { base->ICR |= USART_ICR_IDLECF_Msk; }

	///Clears the receiver timeout flag
	inline void ClearReceiverTimeoutFlag() { base->ICR |= USART_ICR_RTOCF_Msk; }

	///Check if the send register is empty
	inline bool IsTxRegisterEmpty() { return bool(base->ISR & USART_ISR_TXE_TXFNF_Msk); }

	///Check if the tarnsmission complete
	inline bool IsTransComplete() { return bool(base->ISR & USART_ISR_TC_Msk); }

	///Check if the read date register not empty
	inline bool IsReadDataRegNotEmpty() { return bool(base->ISR & USART_ISR_RXNE_RXFNE_Msk); }

	///Check if usart idle status
	inline bool IsUsartIdleStauts() { return bool(base->ISR & USART_ISR_IDLE_Msk); }

	///Check if receiver timeout
	inline bool IsReceiverTimeout() { return bool(base->ISR & USART_ISR_RTOF_Msk); }
};

#endif // !__VK_DRV_USART_H__
