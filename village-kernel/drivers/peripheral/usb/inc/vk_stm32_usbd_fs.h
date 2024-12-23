//###########################################################################
// vk_stm32_usbd_fs.h
// Declarations of the functions that manage stm32 usbd fs
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_STM32_USBD_FS_H__
#define __VK_STM32_USBD_FS_H__

#include "vk_hardware.h"
#include "vk_driver.h"


/// @brief Stm32UsbdFS
class Stm32UsbdFS : public NetworkDriver
{
public:
	/// @brief Config
	struct Config
	{
		uint16_t usb;
	};
private:
	//Members
	Config config;
public:
	/// @brief Methods
	Stm32UsbdFS();
	~Stm32UsbdFS();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	void Close();
};


/// @brief Stm32UsbdFSDrv
class Stm32UsbdFSDrv : public PlatDriver
{
public:
	/// @brief Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__VK_STM32_USBD_FS_H__
