//###########################################################################
// VGA.cpp
// Definitions of the functions that manage x86 VGA
//
// $Copyright: Copyright (C)
//###########################################################################
#include "VGA.h"
#include "Kernel.h"


/// @brief Constructor
VGA::VGA()
{
}


/// @brief
VGA::~VGA()
{
}


/// @brief VGA initialize
void VGA::Initialize()
{
	device.width = 320;
	device.height = 200;
}


/// @brief VGA write reg
/// @param reg 
/// @param value 
void VGA::WriteData(uint16_t reg, uint16_t value)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	videos[reg] = value;
}


/// @brief VGA read reg
/// @param reg 
/// @return 
uint16_t VGA::ReadData(uint16_t reg)
{
	unsigned char* videos = (unsigned char*)0xA0000;
	return videos[reg];
}


/// @brief VGA draw point
/// @param x 
/// @param y 
/// @param color 
void VGA::DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	WriteData((x + y * device.width), color);
}


/// @brief VGA read point
/// @param x 
/// @param y 
/// @return 
uint16_t VGA::ReadPoint(uint16_t x, uint16_t y)
{
	return ReadData((x + y * device.width));
}


/// @brief VGA clear
/// @param color 
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
