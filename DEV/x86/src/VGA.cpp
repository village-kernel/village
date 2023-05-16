//###########################################################################
// VGA.cpp
// Definitions of the functions that manage x86 VGA
//
// $Copyright: Copyright (C)
//###########################################################################
#include "VGA.h"
#include "Kernel.h"


///Constructor
VGA::VGA()
{
}


///VGA initialize
void VGA::Initialize()
{
	device.width = 320;
	device.height = 200;
}


///VGA write reg
void VGA::WriteData(uint16_t reg, uint16_t value)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	videos[reg] = value;
}


///VGA read reg
uint16_t VGA::ReadData(uint16_t reg)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	return videos[reg];
}


///VGA draw point
void VGA::DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	WriteData((x + y * device.width), color);
}


///VGA read point
uint16_t VGA::ReadPoint(uint16_t x, uint16_t y)
{
	return ReadData((x + y * device.width));
}


///VGA clear
void VGA::Clear(uint16_t color)
{
	for (uint16_t y = 0; y < device.height; y++)
	{
		for (uint16_t x = 0; x < device.width; x++)
		{
			DrawPoint(x, y, color);
		}
	}
}


///Register driver
REGISTER_DRIVER(new VGA(), DriverID::_display, vga);
