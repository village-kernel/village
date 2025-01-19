//###########################################################################
// vk_stm32f407_devices.h
// Declarations of the functions that manage stm32f407 devices
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STM32F407_DEVICES_H__
#define __VK_STM32F407_DEVICES_H__

#include "vk_spi_sdcard.h"
#include "vk_spi_w25qxx.h"
#include "vk_stm32_uart.h"
#include "vk_stm32_usb.h"
#include "vk_ili9488.h"


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


/// @brief Stm32UsbDev
class Stm32UsbDev : public PlatDevice
{
private:
	/// @brief Members
	Stm32Usb::Config config;
public:
	/// @brief Methods
	void Config();
};

#endif //!__VK_STM32F407_DEVICES_H__
