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
private:
	//Members
	volatile USB_OTG_GlobalTypeDef* base;
public:
	void Initialize();
};

#endif //!__VK_DRV_USB_H__
