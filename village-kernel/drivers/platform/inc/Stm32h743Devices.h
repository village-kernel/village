//###########################################################################
// Stm32h743Devices.h
// Declarations of the functions that manage stm32h743 devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STM32H743_DEVICES_H__
#define __STM32H743_DEVICES_H__

#include "SdioSdCard.h"
#include "Stm32Uart.h"


/// @brief SpiSdCardDev
class SdioSdCardDev : public PlatDevice
{
private:
	/// @brief Members
	SdioSdCard::Config config;
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

#endif //!__STM32H743_DEVICES_H__
