//###########################################################################
// Usart.h
// Hardware layer class that manages a USART/Serial module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USART_H__
#define __USART_H__

#include "HalHeaders.h"

///Usart
class Usart
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
	volatile uint16_t channel;
	volatile uint32_t base;

	//Methods
	bool IsTxRegisterEmpty();
	bool IsReadDataRegNotEmpty();
public:
	//Methods
	Usart();
	void Initialize(uint16_t channel);
	int Write(uint8_t* txData, uint16_t length);
	int Read(uint8_t* rxData, uint16_t length);
};

#endif //!__USART_H__
