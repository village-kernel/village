//###########################################################################
// vk_drv_i2c.h
// Hardware Layer class that manages a single I2c as master
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_I2C_H__
#define __VK_DRV_I2C_H__

#include "stm32h7xx.h"
#include "vk_drv_gpio.h"


/// @brief I2c
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
	struct Config
	{
        Gpio::Config sclGpio;
        Gpio::Config sdaGpio;
	};
private:
	//Members
	Gpio sclPin;
	Gpio sdaPin;

	//Methods
	void I2cDelay(void);
public:
	//Methods
	void Initialize(Config config);
	void Start();
	void Stop();
	void WriteByte(uint8_t data);	
	uint8_t ReadByte();
	AckType GetAck();
	void PutAck(AckType ack);
};

#endif // !__VK_DRV_I2C_H__
