//###########################################################################
// vk_drv_usb.h
// Hardware Layer class that manage usb module
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_DRV_USB_H__
#define __VK_DRV_USB_H__

#include "stm32f4xx.h"


/// @brief Usb
class Usb
{
public:
	enum Mode
	{
		_DeviceMode = 0,
		_HostMode = 1,
		_DrdMode = 2,
	};

	enum Speed
	{
		_SpeedHigh = 0,
		_SpeedHighInFull = 1,
		_SpeedFull = 3,
	};
private:
	//Static const members
	static const uint32_t dev_endpoints = 9;

	//Members
	volatile USB_OTG_GlobalTypeDef* base;
	volatile USB_OTG_DeviceTypeDef* device;
	volatile uint32_t* pcgcctl;

	//Methods
	Mode GetMode();
	USB_OTG_INEndpointTypeDef* InEndPoint(uint8_t index);
	USB_OTG_OUTEndpointTypeDef* OutEndPoint(uint8_t index);
public:
	//Methods
	Usb();
	void Initialize();
	void InitUsbCore();
	void ConfigDeviceMode();
	void ConfigHostMode();
	void InitUsbDevice();
	void InitEndpoint(uint8_t endpoints);
	void ConfigDevSpeed(uint8_t speed);
	void ConfigTxFifo(uint8_t fifo, uint16_t size);
	void ConfigRxFifo(uint16_t size);
	void FlushTxFifo(uint32_t num);
	void FlushRxFifo();
	void ConnectDevice();
	void DisconnectDevice();
	void EnableInterrupt();
	void DisableInterrupt();
	void Enable();
	void Start();
	void IRQHandler();
};

#endif //!__VK_DRV_USB_H__
