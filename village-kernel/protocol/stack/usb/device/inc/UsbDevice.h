//###########################################################################
// UsbDevice.h
// Declarations of the functions that manage usb device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USB_DEVICE_H__
#define __USB_DEVICE_H__

#include "Kernel.h"
#include "Stack.h"


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

#endif // !__USB_DEVICE_H__
