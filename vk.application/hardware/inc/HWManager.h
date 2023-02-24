//###########################################################################
// HWManager.h
// Declarations of the functions that manage hardware device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_MANAGER_H__
#define __HW_MANAGER_H__

#include "Module.h"
#include "UartSerial.h"
#include "ILI9488.h"
#include "SpiFlash.h"
#include "SdCard.h"
#include "UsbStorage.h"


///HWManager
class HWManager : public Module
{
private:
	//Static members
	static HWManager instance;

	//Methods
	HWManager();
	void SerialInitialize();
	void ILI9488Initialize();
	void FlashInitialize();
	void SdCardInitialize();
	void UsbInitialize();
public:
	//Members
	UartSerial   uartSerial;
	ILI9488      ili9488;
	SpiFlash     spiFlash;
	SdCard       sdcard;
	UsbStorage   usbStorage;

	//Methods
	void Initialize();
	void UpdateParams();
	void FailSafe(int arg);

	///Gets the singleton instance of HWManager
	static inline HWManager* Instance() { return &instance; }
};

#endif // !__HW_MANAGER_H__
