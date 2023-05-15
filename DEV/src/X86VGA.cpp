//###########################################################################
// X86VGA.cpp
// Definitions of the functions that manage x86 VGA
//
// $Copyright: Copyright (C)
//###########################################################################
#include "X86VGA.h"
#include "Kernel.h"


///Constructor
X86VGA::X86VGA()
{
}


///X86VGA initialize
void X86VGA::Initialize()
{
	device.width = 320;
	device.height = 200;
}


///X86VGA write reg
void X86VGA::WriteData(uint16_t reg, uint16_t value)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	videos[reg] = value;
}


///X86VGA read reg
uint16_t X86VGA::ReadData(uint16_t reg)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	return videos[reg];
}


///X86VGA draw point
void X86VGA::DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	WriteData((x + y * device.width), color);
}


///X86VGA read point
uint16_t X86VGA::ReadPoint(uint16_t x, uint16_t y)
{
	return ReadData((x + y * device.width));
}


///X86VGA clear
void X86VGA::Clear(uint16_t color)
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
REGISTER_DRIVER(new X86VGA(), DriverID::_display + 1, vga);
