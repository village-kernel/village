//###########################################################################
// UsbStorage.h
// Declarations of the functions that manage usb storage
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __USB_STORAGE_H__
#define __USB_STORAGE_H__

#include "HalHeaders.h"
#include "Driver.h"

///UsbStorage
class UsbStorage : public Driver
{
private:
	//Methods
	void Mount();
	void Unmount();
public:
	//Methods
	int Open();
	void Close();
};

#endif // !__USB_STORAGE_H__
