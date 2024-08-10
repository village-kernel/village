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
		Usart::Channel  usartCh;
		uint32_t        baudrate;
		bool            enableRTS;
		bool            enableDMA;

		Gpio::Config    txGpio;
		Gpio::Config    rxGpio;
		Gpio::Config    deGpio;

		DmaFifo::Config txDma;
		DmaFifo::Config rxDma;
	};
private:
	//Members
	Usart   usart;
	DmaFifo txFifo;
	DmaFifo rxFifo;
	Config  config;
	bool    isUsed;
private:
	/// @brief Initialize config
	inline void InitConfig()
	{
		config = UART_SERIAL_CONFIG;
	}


	/// @brief Pin config
	inline void PinConfig()
	{
		Gpio gpio;

		gpio.Initialize(config.txGpio);
		gpio.Initialize(config.rxGpio);
		
		if (config.enableRTS)
		{
			gpio.Initialize(config.deGpio);
		}
	}
public:
	/// @brief Constructor
	UartSerial()
		:isUsed(false)
	{
	}


	/// @brief Open
	/// @return 
	bool Open()
	{
		//Return when is used
		if (isUsed) return true;

		//Init config
		InitConfig();

		//Pin config
		PinConfig();

		//Configure usart
		usart.Initialize(config.usartCh);
		usart.SetBaudRate(config.baudrate);
		usart.ConfigPortSettings(Usart::_8Bits, Usart::_NoParity, Usart::_1Stop);

		//Configure usart RTS
		if (config.enableRTS)
		{
			usart.ConfigDriverEnableMode(true, false);
			usart.ConfigReceiverTimeout(true, 39); // 3.5bytes: 3.5 * 11 = 38.5
		}
		
		//Configure usart DMA
		if (config.enableDMA)
		{
			//Enable dma
			usart.ConfigDma();

			//Configure tx fifo
			config.txDma.periphAddr = usart.GetTxAddr();
			txFifo.Open(config.txDma);

			//Configure rx fifo
			config.rxDma.periphAddr = usart.GetRxAddr();
			rxFifo.Open(config.rxDma);
		}

		//Enable usart
		usart.Enable();

		//Set isUsed flag
		isUsed = true;

		return true;
	}


	/// @brief Write data
	/// @param data 
	/// @param size 
	/// @param offset 
	/// @return 
	int Write(uint8_t* data, uint32_t size, uint32_t offset = 0)
	{
		usart.CheckError();

		if (config.enableDMA)
			return txFifo.Write(data, size, offset);
		else
			return usart.Write(data, size, offset);
	}


	/// @brief Read data
	/// @param data 
	/// @param size 
	/// @param offset 
	/// @return 
	int Read(uint8_t* data, uint32_t size, uint32_t offset = 0)
	{
		usart.CheckError();

		if (config.enableDMA)
			return rxFifo.Read(data, size, offset);
		else
			return usart.Read(data, size, offset);
	}


	/// @brief Close
	void Close()
	{
		if (config.enableDMA)
		{
			txFifo.Close();
			rxFifo.Close();
		}
	}
};


///Register driver
REGISTER_DRIVER(new UartSerial(), DriverID::_character, serial0);
