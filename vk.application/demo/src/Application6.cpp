//###########################################################################
// Application6.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application6.h"
#include "Hardware.h"


///Constructor
Application6::Application6()
{
}


///// @brief Read a byte from the specified port
///// @param port 
///// @return result
//uint8_t PortByteIn1(uint16_t port)
//{
//    uint8_t result;
//    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
//    return result;
//}

///// @brief Write a byte to the specified port
///// @param port 
///// @param data 
//void PortByteOut1(uint16_t port, uint8_t data)
//{
//    __asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
//}


///Check if the send register is empty
bool IsTxRegisterEmpty()
{
	return (bool)(PortByteIn(COM1 + COM_LINE_STATUS_Pos) & COM_LINE_STATUS_THRE);
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


///Application6 initialize
void Application6::Initialize()
{
	char data[] = "hello module";

	Write((uint8_t*)data, sizeof(data), 0);
}


///Application6 execute
void Application6::Execute()
{
	char data[] = "hello module";
	while (1)
	{
		Write((uint8_t*)data, sizeof(data), 0);
		thread.Sleep(1000);
	}
}


//Register module
REGISTER_MODULE(new Application6(), (ModuleID::_application + 6), app_6);
