//###########################################################################
// Cursor.cpp
// Definitions of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cursor.h"


/// @brief cursor data
const uint32_t cursordat[] = {
	0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
	0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff,
	0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000,
};


/// @brief Backup data
static uint32_t colorBits[128] = {0};


/// @brief Constructor
Cursor::Cursor()
	:locX(0),
	locY(0)
{}


/// @brief Setup
void Cursor::Setup()
{

}


/// @brief Cursor Read
/// @param x 
/// @param y 
/// @param data 
void Cursor::Read(uint32_t x, uint32_t y, uint32_t* data)
{
	for (uint32_t i = 0; i < 16; i++)
	{
		for (uint32_t j = 0; j < 8; j++)
		{
			if (cursordat[i * 8 + j] != 0xffff)
			{
				data[i * 8 + j] = display->ReadPoint(x + j, y + i);
			}
		}
	}
}


/// @brief Cursor Draw
/// @param x 
/// @param y 
/// @param data 
void Cursor::Draw(uint32_t x, uint32_t y, uint32_t* data)
{
	for (uint32_t i = 0; i < 16; i++)
	{
		for (uint32_t j = 0; j < 8; j++)
		{
			if (cursordat[i * 8 + j] != 0xffff)
			{
				display->DrawPoint(x + j, y + i, data[i * 8 + j]);
			}
		}
	}
}


/// @brief Cursor Show
void Cursor::Show()
{
	locX = GetLocX();
	locY = GetLocY();
	Read(locX, locY, (uint32_t*)colorBits);
	Draw(locX, locY, (uint32_t*)cursordat);
}


/// @brief Cursor Update
void Cursor::Update(int axisX, int axisY)
{
	Draw(locX, locY, (uint32_t*)colorBits);

	locX += axisX;
	locY -= axisY;

	if (locX < 0) locX = 0;
	else if (locX > width) locX = width;
	if (locY < 0) locY = 0;
	else if (locY > height) locY = height;

	Read(locX, locY, (uint32_t*)colorBits);
	Draw(locX, locY, (uint32_t*)cursordat);
}
