//###########################################################################
// I2c.h
// Hardware Layer class that manages a single I2c as master
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef _I2C_H_
#define _I2C_H_

#include "HalHeaders.h"
#include "Gpo.h"

///I2c
class I2c
{
public:
	//Enumerations
	enum AckType
	{
		Ack = 0,
		Nack = 1,
	};

	//Structures
	struct PinConfig
	{
		Gpio::GpioChannel sclCh;
		Gpio::GpioChannel sdaCh;
		uint16_t sclPin;
		uint16_t sdaPin;
	};
private:
	//Members
	Gpo sclPin;
	Gpo sdaPin;

	//Methods
	void I2cDelay(void);
public:
	//Methods
	void Initialize(PinConfig pins);
	void Start();
	void Stop();
	void WriteByte(uint8_t data);	
	uint8_t ReadByte();
	AckType GetAck();
	void PutAck(AckType ack);
};

#endif /* _I2C_H_ */

