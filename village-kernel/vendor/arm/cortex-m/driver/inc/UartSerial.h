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
#include "Dma.h"
#include "DmaFifo.h"
#include "Driver.h"

///UartSerial
class UartSerial : public Driver
{
public:
	//Structures
	struct Config
	{
		bool enableRTS = false;

		uint16_t usartCh;
		uint32_t usartBaudrate;
		Usart::PinConfig usartTxPin;
		Usart::PinConfig usartRxPin;
		Usart::PinConfig usartDePin;

		uint8_t usartTxDmaGroup;
		uint8_t usartRxDmaGroup;
		uint8_t usartTxDmaCh;
		uint8_t usartRxDmaCh;
		uint8_t usartTxDmaReq;
		uint8_t usartRxDmaReq;
	};
private:
	//Static Constants
	static const uint32_t BufferSize = 256;

	//Members
	Dma txDma;
	Usart usart;
	DmaFifo rxFifo;
	Config config;
	uint8_t txBuffer[BufferSize] = { 0 };

	//Methods
	void InitConfig();
	void ChangeBaudrate(uint32_t baudrate);
	void CopyTxData(uint8_t* txData, uint16_t length);
public:
	//Methods
	bool Open();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	void Close();
};

#endif // !__UART_SERIAL_H__
