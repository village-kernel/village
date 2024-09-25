//###########################################################################
// Pic32Uart.cpp
// Definitions of the functions that manage pic32 uart
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Pic32Uart.h"
#include "Kernel.h"
#include "string.h"


/// @brief Constructor
Pic32Uart::Pic32Uart()
{
}


/// @brief Destructor
Pic32Uart::~Pic32Uart()
{
}


/// @brief SetData
/// @param data 
void Pic32Uart::SetData(void* data)
{
	config = *((Config*)data);

	if (config.port < 0 || config.port > 7)
	{
		config.port = 0;
	}
}


/// @brief Check if the send register is empty
bool Pic32Uart::IsTxRegisterEmpty()
{
	return (bool)(PortByteIn(COMX[config.port] + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE);
}


/// @brief Check if the read date register not empty
bool Pic32Uart::IsReadDataRegNotEmpty()
{
	return (bool)(PortByteIn(COMX[config.port] + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_DR);
}


/// @brief Open
bool Pic32Uart::Open()
{
	//Setup serial
	PortByteOut(COMX[config.port] + 1, 0x00);    // Disable all interrupts
	PortByteOut(COMX[config.port] + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	PortByteOut(COMX[config.port] + 0, 0x00);    // Set divisor to 0 (lo byte) 115200 baud
	PortByteOut(COMX[config.port] + 1, 0x00);    //                  (hi byte)
	PortByteOut(COMX[config.port] + 3, 0x03);    // 8 bits, no parity, one stop bit
	PortByteOut(COMX[config.port] + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	PortByteOut(COMX[config.port] + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	PortByteOut(COMX[config.port] + 4, 0x1E);    // Set in loopback mode, test the serial chip
	PortByteOut(COMX[config.port] + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

	//Check if serial is faulty (i.e: not same byte as sent)
	if(PortByteIn(COMX[config.port] + 0) != 0xAE) return false;

	//If serial is not faulty set it in normal operation mode
	//(not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	PortByteOut(COMX[config.port] + 4, 0x0F);

	return true;
}


/// @brief Write data
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Pic32Uart::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	int count = size;

	while (size)
	{
		if (IsTxRegisterEmpty())
		{
			PortByteOut(COMX[config.port], *data++);
			size--;
		}
	}

	return count;
}


/// @brief Read data from rx buffer
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int Pic32Uart::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	uint32_t count = 0;

	while (IsReadDataRegNotEmpty())
	{
		*data++ = PortByteIn(COMX[config.port]);
		if (++count >= size) break;
	}

	return count;
}


/// @brief Close
void Pic32Uart::Close()
{

}


/// @brief Probe
/// @param device 
/// @return 
bool Pic32UartDrv::Probe(PlatDevice* device)
{
	Pic32Uart* serial = new Pic32Uart(); 
	serial->SetID(DriverID::_character);
	serial->SetName(device->GetDriverName());
	serial->SetData(device->GetDriverData());
	device->SetDriver(serial);
	kernel->device.RegisterCharDevice((CharDriver*)device->GetDriver());
	return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Pic32UartDrv::Remove(PlatDevice* device)
{
	kernel->device.UnregisterCharDevice((CharDriver*)device->GetDriver());
	delete (Pic32Uart*)device->GetDriver();
	device->SetDriver(NULL);
	return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Pic32UartDrv(), pic32uart, pic32uartDrv);
