//###########################################################################
// UartSerial.cpp
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "UartSerial.h"
#include "string.h"


///Initializes internal buffers
void UartSerial::Initialize()
{
	//Configure usart
	usart.Initialize(0);
}


///Copy the sent data to the send buffer to avoid accidentally modifying the sent data.
inline void UartSerial::CopyTxData(uint8_t* txData, uint16_t length)
{
	memcpy((uint8_t*)txBuffer, (uint8_t*)txData, length);
}


///Write data via dma.
int UartSerial::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	return usart.Write(data + offset, size);
}


///Read data from rx buffer
int UartSerial::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	return usart.Read(data + offset, size);
}


///Register driver
REGISTER_DRIVER(new UartSerial(), DriverID::_serial, uartSerial);
