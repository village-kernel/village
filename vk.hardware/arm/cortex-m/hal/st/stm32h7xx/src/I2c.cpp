//###########################################################################
// I2c.cpp
// Hardware Layer class that manages a single I2c as master
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "I2c.h"


///Pins Initialize
void I2c::Initialize(PinConfig pins)
{
	//Config scl pin as General purpose output mode with pull up
	sclPin.Initialize(pins.sclCh, pins.sclPin, Gpio::_High);
	
	//Config sda as Output open-drain mode with pull up
	sdaPin.Initialize(pins.sdaCh, pins.sdaPin, Gpio::_High);
	sdaPin.ConfigOutputType(Gpio::_OpenDrain);
}


///I2c delay
inline void I2c::I2cDelay()
{
	volatile uint8_t delayCycles = 250;
	while(delayCycles-- ){}
}


///start condition
void I2c::Start()
{
	sclPin.Clear();
	sdaPin.Set();
	I2cDelay();

	sclPin.Set();
	I2cDelay();
	
	sdaPin.Clear();
	I2cDelay();
	
	sclPin.Clear();
	I2cDelay();
}


///stop condition
void I2c::Stop()
{
	sclPin.Clear();
	sdaPin.Clear();
	I2cDelay();

	sclPin.Set();
	I2cDelay();
	
	sdaPin.Set();
	I2cDelay();
}


///write one byte data
void I2c::WriteByte(uint8_t data)
{ 
	const uint8_t MSB = 0x80;
	
	for(uint8_t bits = 0; bits < 8; bits++)
	{
		sclPin.Clear();
		if (data & MSB)
			sdaPin.Set();
		else
			sdaPin.Clear();
		I2cDelay();
		
		sclPin.Set();
		data <<= 1;
		I2cDelay();
	}
	sclPin.Clear();
	I2cDelay();
}


///read one byte data
uint8_t I2c::ReadByte()
{
	uint8_t data = 0;
	
	sclPin.Clear();
	sdaPin.Set(); 		//Switch to read mode
	
	for(uint8_t bits = 0; bits < 8; bits++)
	{
		sclPin.Clear();
		I2cDelay();
		
		sclPin.Set();
		I2cDelay();
		data = (data << 1) | (sdaPin.GetInputState() ? 1 : 0);
	}
	sclPin.Clear();
	I2cDelay();
	
	return  data;
}


///get ack, 0 : ack ,1 : nack
I2c::AckType I2c::GetAck()
{
	AckType ack = Ack;
	
	sclPin.Clear();
	sdaPin.Set();	//Switch to read mode
	I2cDelay();
	
	sclPin.Set();
	I2cDelay();
	ack = (AckType)sdaPin.GetInputState();
	
	sclPin.Clear();
	I2cDelay();

	return ack;
}


///put ack, 0 : ack, 1 : nack
void I2c::PutAck(AckType ack)
{
	sclPin.Clear();
	sdaPin.Write((Gpio::GpioState)ack);
	I2cDelay();
	
	sclPin.Set();
	I2cDelay();
	
	sclPin.Clear();
	I2cDelay();
}

