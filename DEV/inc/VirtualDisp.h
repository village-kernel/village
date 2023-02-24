//###########################################################################
// VirtualDisp.h
// Declarations of the functions that manage virtual display interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VIRTUAL_DISP_H__
#define __VIRTUAL_DISP_H__

#include <cstdint>

///VirtualDisp
class VirtualDisp
{
public:
	//Enum
	enum Dir
	{
		Up = 0,
		Left,
		Right,
		Down,
	};

	//Device struct
	struct DeviceStruct
	{
		uint32_t id;
		Dir dir;
		uint16_t width;
		uint16_t height;
		uint16_t setXCmd;
		uint16_t setYCmd;
		uint16_t wRamCmd;
		uint16_t rRamCmd;
	};

	//Members
	DeviceStruct device;

	//Methods
	virtual void OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height) = 0;
	virtual void SetCursor(uint16_t x, uint16_t y) = 0;
	virtual void SetDirection(Dir dir) = 0;
	virtual void DrawPoint(uint16_t x, uint16_t y, uint16_t color) = 0;
	virtual uint16_t ReadPoint(uint16_t x, uint16_t y) = 0;
	virtual void Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) = 0;
	virtual void Clear(uint16_t color) = 0;
};

#endif //!__VIRTUAL_DISP_H__
