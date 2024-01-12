//###########################################################################
// VGA.cpp
// Definitions of the functions that manage x86 VGA
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Hardware.h"
#include "Kernel.h"
#include "Driver.h"
#include "LcdDriver.h"


/// @brief VGA
class VGA : public LcdDriver
{
private:
	/// @brief VGA write reg
	/// @param reg 
	/// @param value 
	void WriteData(uint16_t reg, uint16_t value)
	{
		unsigned char* videos = (unsigned char*)0xA0000;
		videos[reg] = value;
	}


	/// @brief VGA read reg
	/// @param reg 
	/// @return 
	uint16_t ReadData(uint16_t reg)
	{
		unsigned char* videos = (unsigned char*)0xA0000;
		return videos[reg];
	}
public:
	/// @brief Constructor
	VGA()
	{
	}


	/// @brief Destructor
	~VGA()
	{
	}


	/// @brief VGA initialize
	void Initialize()
	{
		device.width = 320;
		device.height = 200;
	}


	/// @brief VGA draw point
	/// @param x 
	/// @param y 
	/// @param color 
	void DrawPoint(uint16_t x, uint16_t y, uint16_t color)
	{
		WriteData((x + y * device.width), color);
	}


	/// @brief VGA read point
	/// @param x 
	/// @param y 
	/// @return 
	uint16_t ReadPoint(uint16_t x, uint16_t y)
	{
		return ReadData((x + y * device.width));
	}


	/// @brief VGA clear
	/// @param color 
	void Clear(uint16_t color = 0)
	{
		for (uint16_t y = 0; y < device.height; y++)
		{
			for (uint16_t x = 0; x < device.width; x++)
			{
				DrawPoint(x, y, color);
			}
		}
	}
};


/// @brief VGADrv
class VGADrv : public Driver
{
private:
	//Members
	VGA* vga;
public:
	/// @brief Constructor
	VGADrv()
	{
		vga = new VGA;
	}


	/// @brief Destructor
	~VGADrv()
	{
		delete vga;
	}


	/// @brief 
	void Initialize()
	{		
		vga->Initialize();
	}


	/// @brief IOCtrl
	/// @param cmd 
	/// @param data 
	/// @return 
	int IOCtrl(uint8_t cmd, void* data)
	{
		LcdDriver** lcd = (LcdDriver**)data;

		*lcd = vga;

		return 0;
	}
};


///Register driver
REGISTER_DRIVER(new VGADrv(), DriverID::_display, display);
