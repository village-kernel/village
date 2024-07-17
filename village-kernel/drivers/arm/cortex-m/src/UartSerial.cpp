//###########################################################################
// UartSerial.cpp
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HwConfig.h"
#include "Hardware.h"
#include "DmaFifo.h"
#include "Driver.h"
#include "Kernel.h"
#include "string.h"


/// @brief UartSerial
class UartSerial : public Driver
{
public:
	//Structures
	struct Config
	{
		bool enableRTS = false;
		bool enableDMA = true;

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
private:
	/// @brief Initialize config
	void InitConfig()
	{
		//Config uart serial
		config.usartCh = UART_SERIAL_CHANNEL;
		config.usartBaudrate = UART_SERIAL_BAUD_RATE;

		//Config uart rx pin
		config.usartRxPin.ch = UART_SERIAL_RX_CH;
		config.usartRxPin.pin = UART_SERIAL_RX_PIN;
		config.usartRxPin.alt = UART_SERIAL_RX_AF_NUM;

		//Config uart tx pin
		config.usartTxPin.ch = UART_SERIAL_TX_CH;
		config.usartTxPin.pin = UART_SERIAL_TX_PIN;
		config.usartTxPin.alt = UART_SERIAL_TX_AF_NUM;

		//Config uart rx dma
		config.usartRxDmaGroup = UART_SERIAL_RX_DMA_GROUP;
		config.usartRxDmaCh = UART_SERIAL_RX_DMA_CHANNEL;
		config.usartRxDmaReq = UART_SERIAL_RX_DMA_REQUEST;

		//Config uart tx dma
		config.usartTxDmaGroup = UART_SERIAL_TX_DMA_GROUP;
		config.usartTxDmaCh = UART_SERIAL_TX_DMA_CHANNEL;
		config.usartTxDmaReq = UART_SERIAL_TX_DMA_REQUEST;
		
		//COnfig enable dma
		config.enableDMA = UART_SERIAL_ENABLEDMA;
	}


	/// @brief Copy the sent data to the send buffer to avoid accidentally modifying the sent data.
	/// @param txData 
	/// @param length 
	inline void CopyTxData(uint8_t* txData, uint16_t length)
	{
		memcpy((uint8_t*)txBuffer, (uint8_t*)txData, length);
	}
public:
	/// @brief Initializes internal buffers
	/// @return 
	bool Open()
	{
		//Init config
		InitConfig();

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

		return true;
	}


	/// @brief Write data via dma.
	/// @param data 
	/// @param size 
	/// @param offset 
	/// @return 
	int Write(uint8_t* data, uint32_t size, uint32_t offset)
	{
		usart.CheckError();

		if (config.enableDMA)
		{
			if (txDma.IsReady())
			{
				CopyTxData(data + offset, size);

				//Reset pipeline, sync bus and memory access
				__asm ("dmb\n" "dsb\n" "isb\n");

				txDma.Disable();
				txDma.ClearTransferCompleteFlag();
				txDma.SetMemAddr0(txBuffer);
				txDma.SetDataLen(size);
				txDma.Enable();

				return size;
			}
		}
		else
		{
			if (0 == usart.Write(data + offset, size)) return true;
		}

		return 0;
	}


	/// @brief Read data from rx buffer
	/// @param data 
	/// @param size 
	/// @param offset 
	/// @return 
	int Read(uint8_t* data, uint32_t size, uint32_t offset)
	{
		usart.CheckError();

		if (config.enableDMA)
		{
			uint32_t readSize = 0;

			rxFifo.Update();

			while (rxFifo.Length())
			{
				data[offset + readSize++] = rxFifo.Dequeue();

				if (readSize >= size) break;
			}

			return readSize;
		}
		else
		{
			return usart.Read(data + offset, size);
		}
	}


	/// @brief Close
	void Close()
	{

	}
};


///Register driver
REGISTER_DRIVER(new UartSerial(), DriverID::_character, serial0);
