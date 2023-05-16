//###########################################################################
// UartSerial.h
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally. This class is *not* thread-safe.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __UART_SERIAL_H__
#define __UART_SERIAL_H__

#include "HalHeaders.h"
#include "Usart.h"
#include "Driver.h"

///UartSerial
class UartSerial : public Driver
{
private:
	//Static Constants
	static const uint32_t BufferSize = 1024;

	//Members
	Usart usart;
	uint8_t txBuffer[BufferSize] = { 0 };

	//Methods
	void CopyTxData(uint8_t* txData, uint16_t length);
public:
	//Methods
	void Initialize();
	void UpdataParams();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
};

#endif // !__UART_SERIAL_H__
