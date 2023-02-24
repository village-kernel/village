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
#include "VirtualSerial.h"
#include "Usart.h"
#include "Dma.h"
#include "DmaFifo.h"


///UartSerial
class UartSerial : public VirtualSerial
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
	static const uint32_t BufferSize = 1024;

	//Members
	Dma txDma;
	Usart usart;
	DmaFifo rxFifo;
	uint8_t txBuffer[BufferSize] = { 0 };

	//Methods
	void CopyTxData(uint8_t* txData, uint16_t length);
public:
	//Methods
	void Initialize(Config config);
	void ChangeBaudrate(uint32_t baudrate);
	void Execute();
	bool SendBytes(uint8_t* txData, uint16_t length, bool enaDma = true);
	bool HasMessage();
	
	///Indicates whether RX buffer has data
	inline bool HasBytes() { return (rxFifo.Length() > 0); }

	///Read a single byte from the RX buffer.
	inline uint8_t ReadByte() { return rxFifo.Dequeue(); }

	///Clear receive buffer
	inline void ClearReceiveBuffer() { rxFifo.Clear(); }
};

#endif // !__UART_SERIAL_H__

