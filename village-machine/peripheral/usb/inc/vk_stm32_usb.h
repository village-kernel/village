//###########################################################################
// vk_stm32_usb.h
// Declarations of the functions that manage stm32 usb
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STM32_USB_H__
#define __VK_STM32_USB_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_drv_gpio.h"
#include "vk_drv_nvic.h"
#include "vk_drv_usb.h"


/// @brief Stm32Usb
class Stm32Usb : public CharDriver, public Class
{
public:
	/// @brief Config
	struct Config
	{
		uint32_t irq;

		Gpio::Config dmGpio;
		Gpio::Config dpGpio;
	};
private:
	/// @brief Members
	Config config;
	Nvic nvic;
	Usb usb;
	bool isUsed;

	/// @brief Methods
	void PinConfig();
	void UsbHandler();
public:
	/// @brief Methods
	Stm32Usb();
	~Stm32Usb();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	void Close();
};


/// @brief Stm32UsbDrv
class Stm32UsbDrv : public PlatDriver
{
public:
	/// @brief Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__VK_STM32_USB_H__
