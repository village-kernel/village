//###########################################################################
// LcdDriver.h
// Specifies the interface for all classes that contain driver logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

#include "stdint.h"
#include "stddef.h"


///LcdDrirver interface
class LcdDriver
{
public:
	//Structures
	struct DeviceInfo
	{
		uint16_t  width;
		uint16_t  height;
	};

	//Members
	DeviceInfo device;
public:
	//Constructor
	LcdDriver()  {}

	//Deconstructor
	virtual ~LcdDriver() {}

	//Methods
	virtual void DrawPoint(uint16_t x, uint16_t y, uint16_t color) = 0;
	virtual uint16_t ReadPoint(uint16_t x, uint16_t y) = 0;
	virtual void Clear(uint16_t color) = 0;
};

#endif //!__LCD_DRIVER_H__
