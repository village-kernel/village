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
public:
	//Enumerations
	enum DataBits
	{
		_5Bits = 0,
		_6Bits = 1,
		_7Bits = 2,
		_8Bits = 3,
	};

	enum Parity
	{
		_NoParity = 0,
		_ODDParity = 1,
		_EvenParity = 2,
		_MarkParity = 3,
		_SpaceParity = 4,
	};

	enum StopBits
	{
		_1Stop = 0,
		_1AndHalfStop = 1,
	};
private:
	//Members
	volatile uint16_t channel;
	volatile uint32_t base;
public:
	//Methods
	Usart();
	void Initialize(uint16_t channel);
	void ConfigPortSettings(DataBits dataBits, Parity parity, StopBits stopBits);
	void ConfigDriverEnableMode(bool usingDEM = true, bool polarity = false);
	void ConfigReceiverTimeout(bool enable, uint32_t rto = 0, uint8_t blen = 0);
	void ConfigDma(bool dmaTxEnable = true, bool dmaRxEnable = true);
	void SetBaudRate(uint32_t baudRate, bool over8 = false);
	void CheckError();
	int Write(uint8_t* txData, uint16_t length);
	int Read(uint8_t* rxData, uint16_t length);

	///Enables operation of the USART peripheral
	inline void Enable() { }

	///Disables operation of the USART peripheral
	inline void Disable() { }

	///Gets the address of the transmit data register
	inline uint32_t* GetTxAddr() { return 0; }

	///Gets the address of the receive data register
	inline uint32_t* GetRxAddr() { return 0; }

	///Checks for Framing Errors
	inline bool CheckFramingError() { return 0; }

	///Clears the Framing Error flag
	inline void ClearFramingError() { }

	///Clears the receiver timeout flag, not support
	inline void ClearReceiverTimeoutFlag() {  }

	///Check if the send register is empty
	inline bool IsTxRegisterEmpty() { return (bool)(PortByteIn(base + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE); }

	///Check if the read date register not empty
	inline bool IsReadDataRegNotEmpty() { return (bool)(PortByteIn(base + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_DR); }

	///Check if receiver timeout, not support
	inline bool IsReceiverTimeout() { return false; }
};

#endif //!__USART_H__
