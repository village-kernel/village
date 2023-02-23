//###########################################################################
// UsbStorage.h
// Declarations of the functions that manage usb storage
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USB_STORAGE_H__
#define __USB_STORAGE_H__

#include "HalHeaders.h"

///UsbStorage
class UsbStorage
{
public:
	//Methods
	void Initialize();
	void Mount();
	void Unmount();
};

#endif // !__USB_STORAGE_H__
