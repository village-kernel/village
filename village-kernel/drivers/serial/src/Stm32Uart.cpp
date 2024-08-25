//###########################################################################
// Stm32Uart.cpp
// Definitions of the functions that manage stm32 uart
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Stm32Uart.h"
#include "Kernel.h"


/// @brief Constructor
Stm32Uart::Stm32Uart()
	:isUsed(false)
{
}


/// @brief Destructor
Stm32Uart::~Stm32Uart()
{
}


/// @brief SetData
/// @param data 
void Stm32Uart::SetData(void* data)
{
	config = *((Config*)data);
}


/// @brief Pin config
inline void Stm32Uart::PinConfig()
{
	Gpio gpio;

	gpio.Initialize(config.txGpio);
	gpio.Initialize(config.rxGpio);
	
	if (config.enableRTS)
	{
		gpio.Initialize(config.deGpio);
	}
}


/// @brief Open
/// @return 
bool Stm32Uart::Open()
{
	//Return when is used
	if (isUsed) return true;

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
int Stm32Uart::Write(uint8_t* data, uint32_t size, uint32_t offset)
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
int Stm32Uart::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	usart.CheckError();

	if (config.enableDMA)
		return rxFifo.Read(data, size, offset);
	else
		return usart.Read(data, size, offset);
}


/// @brief Close
void Stm32Uart::Close()
{
	if (config.enableDMA)
	{
		txFifo.Close();
		rxFifo.Close();
	}
	isUsed = false;
}


/// @brief Probe
/// @param device 
/// @return 
bool Stm32UartDrv::Probe(PlatDevice* device)
{
	Stm32Uart* serial = new Stm32Uart(); 
	serial->SetID(DriverID::_character);
	serial->SetName(device->GetDriverName());
	serial->SetData(device->GetDriverData());
	device->SetDriver(serial);
	kernel->device.RegisterCharDevice((CharDevice*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Stm32UartDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterCharDevice((CharDevice*)device->GetDriver());
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Stm32UartDrv(), stm32uart);
