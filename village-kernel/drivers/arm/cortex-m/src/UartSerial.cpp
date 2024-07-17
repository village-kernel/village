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

		DmaFifo::Config usartTxDma;
		DmaFifo::Config usartRxDma;
	};
private:
	//Members
	Usart usart;
	DmaFifo txFifo;
	DmaFifo rxFifo;
	Config config;
private:
	/// @brief Initialize config
	void InitConfig()
	{
		//Config uart serial
		config.usartCh = UART_SERIAL_CHANNEL;
		config.usartBaudrate = UART_SERIAL_BAUD_RATE;

		//Config uart tx pin
		config.usartTxPin.ch = UART_SERIAL_TX_CH;
		config.usartTxPin.pin = UART_SERIAL_TX_PIN;
		config.usartTxPin.alt = UART_SERIAL_TX_AF_NUM;

		//Config uart rx pin
		config.usartRxPin.ch = UART_SERIAL_RX_CH;
		config.usartRxPin.pin = UART_SERIAL_RX_PIN;
		config.usartRxPin.alt = UART_SERIAL_RX_AF_NUM;

		//Config uart tx dma
		config.usartTxDma.group = UART_SERIAL_TX_DMA_GROUP;
		config.usartTxDma.channel = UART_SERIAL_TX_DMA_CHANNEL;
		config.usartTxDma.request = UART_SERIAL_TX_DMA_REQUEST;
		config.usartTxDma.isReadFifo = false;

		//Config uart rx dma
		config.usartRxDma.group = UART_SERIAL_RX_DMA_GROUP;
		config.usartRxDma.channel = UART_SERIAL_RX_DMA_CHANNEL;
		config.usartRxDma.request = UART_SERIAL_RX_DMA_REQUEST;
		config.usartRxDma.isReadFifo = true;
		
		//COnfig enable dma
		config.enableDMA = UART_SERIAL_ENABLEDMA;
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

		//Configure tx fifo
		config.usartTxDma.periphAddr = usart.GetTxAddr();
		txFifo.Open(config.usartTxDma);

		//Configure rx fifo
		config.usartRxDma.periphAddr = usart.GetRxAddr();
		rxFifo.Open(config.usartRxDma);

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
			return txFifo.Write(data, size, offset);
		else
			return usart.Write(data + offset, size);
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
			return rxFifo.Read(data, size, offset);
		else
			return usart.Read(data + offset, size);
	}


	/// @brief Close
	void Close()
	{
		txFifo.Close();
		rxFifo.Close();
	}
};


///Register driver
REGISTER_DRIVER(new UartSerial(), DriverID::_character, serial0);
