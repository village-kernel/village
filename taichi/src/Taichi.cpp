//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Taichi.h"
#include "i386.h"


/// @brief Constructor
Taichi::Taichi()
{
}


/// @brief Deconstructor
Taichi::~Taichi()
{
}


///Check if the send register is empty
bool IsTxRegisterEmpty()
{
	return (bool)(PortByteIn(COM1 + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE);
}

void Init()
{
	uint32_t port = COM1;

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

///Write data via dma.
int Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	int count = size;

	while (size)
	{
		if (IsTxRegisterEmpty())
		{
			PortByteOut(COM1, *data++);
			size--;
		}
	}

	return count;
}

/// @brief Initialize
void Taichi::Initialize()
{
	Init();
	char data[] = "hello taichi init\r\n";
	Write((uint8_t*)data, sizeof(data), 0);
}


/// @brief Execute
void Taichi::Execute()
{
	char data[] = "hello taichi execute\r\n";
	Write((uint8_t*)data, sizeof(data), 0);
}


/// @brief main
extern "C" void _start()
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
}
