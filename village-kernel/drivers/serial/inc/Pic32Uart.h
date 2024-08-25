//###########################################################################
// Pic32Uart.h
// Declarations of the functions that manage pic32 uart
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __PIC32_UART_H__
#define __PIC32_UART_H__

#include "Driver.h"
#include "Kernel.h"
#include "Hardware.h"


/// @brief Pic32Uart
class Pic32Uart : public CharDevice
{
public:
	/// @brief Config
	struct Config
	{
		uint16_t port;
	};
	
	//Enumerations
	enum DataBits
	{
		_5Bits = 0,
		_6Bits = 1,
		_7Bits = 2,
		_8Bits = 3,
	};

	enum Parity
	{
		_NoParity = 0,
		_ODDParity = 1,
		_EvenParity = 2,
		_MarkParity = 3,
		_SpaceParity = 4,
	}; 

	enum StopBits
	{
		_1Stop = 0,
		_1AndHalfStop = 1,
	};
private:
	//Members
	Config config;
	uint32_t COMX[8] = {COM1, COM2, COM3, COM4, COM5, COM6, COM7 };

	/// @brief Methods
	bool IsTxRegisterEmpty();
	bool IsReadDataRegNotEmpty();
public:
	/// @brief Methods
	Pic32Uart();
	~Pic32Uart();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	/// @return 
	bool Open();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	void Close();
};


/// @brief Pic32UartDrv
class Pic32UartDrv : public PlatDriver
{
public:
	/// @brief Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__PIC32_UART_H__
