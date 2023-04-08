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
	//Enumerates
	enum Direction
	{
		Up = 0,
		Left,
		Right,
		Down,
	};

	//Structures
	struct DeviceInfo
	{
		uint32_t  id;
		uint16_t  width;
		uint16_t  height;
		uint16_t  setXCmd;
		uint16_t  setYCmd;
		uint16_t  wRamCmd;
		uint16_t  rRamCmd;
		Direction dir;
	};

	//Members
	DeviceInfo device;
public:
	//Methods
	virtual void Initialize() = 0;
	virtual void OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
	virtual void SetCursor(uint16_t x, uint16_t y) = 0;
	virtual void Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) = 0;
	virtual void Clear(uint16_t color) = 0;
	virtual void DrawPoint(uint16_t x, uint16_t y, uint16_t color) = 0;
	virtual uint16_t ReadPoint(uint16_t x, uint16_t y) = 0;
};

#endif //!__LCD_DRIVER_H__
