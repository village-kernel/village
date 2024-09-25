//###########################################################################
// UsbHost.h
// Declarations of the functions that manage usb host
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USB_HOST_H__
#define __USB_HOST_H__

#include "Kernel.h"
#include "Stack.h"


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

#endif // !__USB_HOST_H__
