//###########################################################################
// Serial.cpp
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Serial.h"
#include "string.h"


///Initializes internal buffers
void Serial::Initialize()
{
	uint8_t channel = 0;

	//Select serial port
	switch (channel)
	{
		case 0: port = COM1; break;
		case 1: port = COM2; break;
		case 2: port = COM3; break;
		case 3: port = COM4; break;
		case 4: port = COM5; break;
		case 5: port = COM6; break;
		case 6: port = COM7; break;
		case 7: port = COM8; break;
		default: port = COM1; break;
	}

	//Setup serial
	PortByteOut(port + 1, 0x00);    // Disable all interrupts
	PortByteOut(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	PortByteOut(port + 0, 0x00);    // Set divisor to 0 (lo byte) 115200 baud
	PortByteOut(port + 1, 0x00);    //                  (hi byte)
	PortByteOut(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	PortByteOut(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	PortByteOut(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	PortByteOut(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
	PortByteOut(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

	//Check if serial is faulty (i.e: not same byte as sent)
	if(PortByteIn(port + 0) != 0xAE) return;

	//If serial is not faulty set it in normal operation mode
	//(not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	PortByteOut(port + 4, 0x0F);
}


///Check if the send register is empty
bool Serial::IsTxRegisterEmpty()
{
	return (bool)(PortByteIn(port + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE);
}


///Write data via dma.
int Serial::Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	int count = size;

	while (size)
	{
		if (IsTxRegisterEmpty())
		{
			PortByteOut(port, *data++);
			size--;
		}
	}

	return count;
}


///Check if the read date register not empty
bool Serial::IsReadDataRegNotEmpty()
{
	return (bool)(PortByteIn(port + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_DR);
}


///Read data from rx buffer
int Serial::Read(uint8_t* data, uint32_t size, uint32_t offset)
{
	uint32_t count = 0;

	while (IsReadDataRegNotEmpty())
	{
		*data++ = PortByteIn(port);
		if (++count >= size) break;
	}

	return count;
}


///Register driver
REGISTER_DRIVER(new Serial(), DriverID::_serial, serial);
