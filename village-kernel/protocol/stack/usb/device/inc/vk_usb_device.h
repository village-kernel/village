//###########################################################################
// vk_usb_device.h
// Declarations of the functions that manage usb device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_USB_DEVICE_H__
#define __VK_USB_DEVICE_H__

#include "vk_kernel.h"
#include "vk_stack.h"


/// @brief UsbDevice
class UsbDevice : public Stack
{
public:
	/// @brief Methods
	UsbDevice();
	~UsbDevice();
	void Setup();
	void Exit();
};

#endif // !__VK_USB_DEVICE_H__