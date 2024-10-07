//###########################################################################
// Cursor.cpp
// Definitions of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cursor.h"


/// @brief cursor data
const uint32_t cursorDat[] = {
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
			if (cursorDat[i * 8 + j] != 0xffff)
			{
				data[i * 8 + j] = drawing->ReadingPoint(x + j, y + i);
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
			if (cursorDat[i * 8 + j] != 0xffff)
			{
				drawing->DrawingPoint(x + j, y + i, data[i * 8 + j]);
			}
		}
	}
}


/// @brief 
void Cursor::InitContent()
{
	locX = GetLocX();
	locY = GetLocY();
}


/// @brief Cursor Show
void Cursor::DrawContent()
{
	static int lastLocX = 0;
	static int lastLocY = 0;
	static bool isRevert = false;

	if (lastLocX != locX || lastLocY != locY)
	{
		if (true == isRevert)
		{
			Draw(lastLocX, lastLocY, colorBits);
		}

		Read(locX, locY, (uint32_t*)colorBits);
		Draw(locX, locY, (uint32_t*)cursorDat);
		
		lastLocX = locX;
		lastLocY = locY;

		isRevert = true;
	}
}


/// @brief Cursor Update
void Cursor::InputAxis(int axisX, int axisY, int axisZ)
{
	locX += axisX;
	locY -= axisY;

	if (locX < 0) locX = 0;
	else if (locX > width) locX = width;
	if (locY < 0) locY = 0;
	else if (locY > height) locY = height;

	isChange = true;
}
