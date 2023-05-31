//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Taichi.h"
#include "stdio.h"
#include "Hardware.h"


/// @brief Constructor
Taichi::Taichi()
{
}


/// @brief Deconstructor
Taichi::~Taichi()
{
}

/// @brief Read a byte from the specified port
/// @param port 
/// @return result
uint8_t PortByteIn1(uint16_t port)
{
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

/// @brief Write a byte to the specified port
/// @param port 
/// @param data 
void PortByteOut1(uint16_t port, uint8_t data)
{
    __asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}


///Check if the send register is empty
bool IsTxRegisterEmpty()
{
	return (bool)(PortByteIn1(COM1 + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE);
}

///Write data via dma.
int Write(uint8_t* data, uint32_t size, uint32_t offset)
{
	int count = size;

	while (size)
	{
		if (IsTxRegisterEmpty())
		{
			PortByteOut1(COM1, *data++);
			size--;
		}
	}

	return count;
}

/// @brief Initialize
void Taichi::Initialize()
{
	char data[] = "hello taichi init";
	Write((uint8_t*)data, sizeof(data), 0);
}


/// @brief Execute
void Taichi::Execute()
{
	char data[] = "hello taichi execute";
	Write((uint8_t*)data, sizeof(data), 0);
}


/// @brief main
extern "C" int main()
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
	return 0;
}
