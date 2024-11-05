//###########################################################################
// vk_usb_host.h
// Declarations of the functions that manage usb host
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_USB_HOST_H__
#define __VK_USB_HOST_H__

#include "vk_kernel.h"
#include "vk_stack.h"


/// @brief UsbHost
class UsbHost : public Stack
{
public:
	/// @brief Methods
	UsbHost();
	~UsbHost();
	void Setup();
	void Exit();
};

#endif // !__VK_USB_HOST_H__
