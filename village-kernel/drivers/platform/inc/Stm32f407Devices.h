//###########################################################################
// Stm32f407Devices.h
// Declarations of the functions that manage stm32f407 devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STM32F407_DEVICES_H__
#define __STM32F407_DEVICES_H__

#include "SpiSdCard.h"
#include "SpiW25qxx.h"
#include "ILI9488.h"
#include "Stm32Uart.h"


/// @brief SpiSdCardDev
class SpiSdCardDev : public PlatDevice
{
private:
	/// @brief Members
	SpiSdCard::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief SpiW25Q64Dev
class SpiW25Q64Dev : public PlatDevice
{
private:
	/// @brief Members
	SpiW25qxx::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief ILI9488Dev
class ILI9488Dev : public PlatDevice
{
private:
	/// @brief Members
	ILI9488::Config config;
public:
	/// @brief Methods
	void Config();
};


/// @brief Stm32UartDev
class Stm32UartDev : public PlatDevice
{
private:
	/// @brief Members
	Stm32Uart::Config config;
public:
	/// @brief Methods
	void Config();
};

#endif //!__STM32F407_DEVICES_H__
