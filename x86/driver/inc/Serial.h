//###########################################################################
// Serial.h
// Provides a simple interface to transmit and receive bytes via the USART 
// module. DMA is used to minimize CPU usage. All buffers are managed 
// by the class internally. This class is *not* thread-safe.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "Hardware.h"
#include "Driver.h"

///Serial
class Serial : public Driver
{
public:
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
	volatile uint32_t port;

	//Methods
	bool IsTxRegisterEmpty();
	bool IsReadDataRegNotEmpty();
public:
	//Methods
	void Initialize();
	void UpdataParams();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
};

#endif // !__SERIAL_H__
