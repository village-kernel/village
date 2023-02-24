//###########################################################################
// UartSerial.cpp
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "UartSerial.h"
#include "string.h"


///Initializes internal buffers
void UartSerial::Initialize(UartSerial::Config config)
{
	//Configure usart
	usart.Initialize(config.usartCh);
	usart.ConfigPin(config.usartTxPin);
	usart.ConfigPin(config.usartRxPin);
	if (config.enableRTS) usart.ConfigPin(config.usartDePin);
	usart.SetBaudRate(config.usartBaudrate);
	usart.ConfigPortSettings(Usart::_8Bits, Usart::_NoParity, Usart::_1Stop);
	usart.ConfigDriverEnableMode(true, false);
	usart.ConfigReceiverTimeout(true, 39); // 3.5bytes: 3.5 * 11 = 38.5
	usart.ConfigDma();
	usart.Enable();

	//Configure rx fifo
	rxFifo.Initialize(config.usartRxDmaGroup, config.usartRxDmaCh, config.usartRxDmaReq, usart.GetRxAddr());
	rxFifo.Enable();
	rxFifo.Clear();

	//Configure tx dma
	txDma.Initialize(config.usartTxDmaGroup, config.usartTxDmaCh);
	txDma.ConfigDirAndDataWidth(Dma::_MemoryToPeriph, Dma::_8Bits);
	txDma.ConfigPriority(Dma::_VeryHigh);
	txDma.SetPeriphAddr(usart.GetTxAddr());
	txDma.ConfigIncMode(true, false);
	txDma.ConfigRequest(config.usartTxDmaReq);
}


///Change serial baudrate
void UartSerial::ChangeBaudrate(uint32_t baudrate)
{
	usart.Disable();
	usart.SetBaudRate(baudrate);
	usart.Enable();
}


///Updates contents of the RX buffer and sends out out data from the TX buffer if needed.
///This function should be called periodically, however it is not time senstive.
void UartSerial::Execute()
{
	usart.CheckError();
	rxFifo.Update();
}


///Copy the sent data to the send buffer to avoid accidentally modifying the sent data.
inline void UartSerial::CopyTxData(uint8_t* txData, uint16_t length)
{
	memcpy((uint8_t*)txBuffer, (uint8_t*)txData, length);
}


///Instructs the manager to attempt to transmit data via dma, returns whether data
///was queued up for transmission.
bool UartSerial::SendBytes(uint8_t* txData, uint16_t length, bool enaDma)
{
	usart.CheckError();

	if (enaDma)
	{
		if (txDma.IsReady())
		{
			CopyTxData(txData, length);

			//Reset pipeline, sync bus and memory access
			__asm ("dmb\n" "dsb\n" "isb\n");

			txDma.Disable();
			txDma.ClearTransferCompleteFlag();
			txDma.SetMemAddr0(txBuffer);
			txDma.SetDataLen(length);
			txDma.Enable();

			return true;
		}
	}
	else
	{
		if (0 == usart.Write(txData, length)) return true;
	}

	return false;
}


///Indicates whether has message
bool UartSerial::HasMessage()
{
	if (usart.IsReceiverTimeout())
	{
		usart.ClearReceiverTimeoutFlag();
		return true;
	}
	return false;
}
