//###########################################################################
// Dispaly.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Display.h"
#include "stdarg.h"
#include "stdio.h"


/// @brief Constructor
Display::Display()
{
}


/// @brief Destrucotr
Display::~Display()
{
	
}


///Display Initialize
void Display::Initialize(FBDriver* fbdev)
{
	this->fbdev = fbdev;
	Clear();
}


/// @brief Display draw point
/// @param x 
/// @param y 
/// @param color 
void Display::DrawPoint(uint32_t x, uint32_t y, uint32_t color)
{
	fbdev->DrawPoint(x, y, color);
}


/// @brief Display read point
/// @param x 
/// @param y 
/// @return 
uint32_t Display::ReadPoint(uint32_t x, uint32_t y)
{
	return fbdev->ReadPoint(x, y);
}


/// @brief Display clear
/// @param color 
void Display::Clear(uint32_t color)
{
	fbdev->Clear(color);
}


/// @brief Display draw line
/// @param x0 
/// @param y0 
/// @param x1 
/// @param y1 
/// @param color 
void Display::DrawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
	int32_t xError = 0, yError = 0, distance = 0;
	int32_t xIncrease = 0, yIncrease = 0;
	
	int32_t xDelta = x1 - x0;
	int32_t yDelta = y1 - y0;
	int32_t pointX = x0;
	int32_t pointY = y0;
	
	if (xDelta > 0)
	{
		xIncrease = 1;
	}
	else if (xDelta == 0)
	{
		xIncrease = 0;
	}
	else
	{
		xIncrease = -1;
		xDelta = -xDelta; 
	}

	if (yDelta > 0)
	{
		yIncrease = 1;
	}
	else if (yDelta == 0)
	{
		yIncrease = 0;
	}
	else
	{
		yIncrease = -1;
		yDelta = -yDelta; 
	}

	if (xDelta > yDelta)
	{
		distance = xDelta;
	}
	else
	{
		distance = yDelta;
	}

	for (uint32_t point = 0; point <= (uint32_t)(distance + 1); point++)
	{
		DrawPoint(pointX, pointY, color);
		xError += xDelta;
		yError += yDelta;
		if (xError > distance)
		{
			xError -= distance;
			pointX += xIncrease;
		}
		if (yError > distance)
		{
			yError -= distance;
			pointY += yIncrease;
		}
	}
}


/// @brief Display draw rectangle
/// @param x0 
/// @param y0 
/// @param x1 
/// @param y1 
/// @param color 
void Display::DrawRectangle(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color)
{
	DrawLine(x0, y0, x1, y0, color);
	DrawLine(x0, y0, x0, y1, color);
	DrawLine(x0, y1, x1, y1, color);
	DrawLine(x1, y0, x1, y1, color);
}


/// @brief Display draw circle
/// @param x 
/// @param y 
/// @param r 
/// @param color 
void Display::DrawCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t color)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);

	while (xOffset <= yOffset)
	{
		DrawPoint(x + xOffset, y - yOffset, color);             //5
		DrawPoint(x + yOffset, y - xOffset, color);             //0
		DrawPoint(x + yOffset, y + xOffset, color);             //4
		DrawPoint(x + xOffset, y + yOffset, color);             //6
		DrawPoint(x - xOffset, y + yOffset, color);             //1
		DrawPoint(x - yOffset, y + xOffset, color);             //3
		DrawPoint(x - xOffset, y - yOffset, color);             //2
		DrawPoint(x - yOffset, y - xOffset, color);             //7
		xOffset++;
		
		if (nextPoint < 0)
		{
			nextPoint += 4 * xOffset + 6;
		}
		else
		{
			nextPoint += 10 + 4 * (xOffset - yOffset);
			yOffset--;
		}
	}
}


/// @brief Display show char
/// @param x 
/// @param y 
/// @param charVal 
/// @param fontSize 
/// @param mode 
/// @param color 
void Display::ShowChar(uint32_t x, uint32_t y, uint8_t charVal, FontSize fontSize, DisplayMode mode, uint32_t color)
{
	const uint16_t PointMask = 0x0001;

	uint16_t charLine = 0;
	uint16_t charIndex = charVal - ' ';
	uint8_t rowSize = fontSize;
	uint8_t colSize = fontSize >> 1;

	for (uint8_t row = 0; row < rowSize; row++)
	{
		if (Font16 == fontSize)
		{
			charLine = ASCII_16[charIndex][row];
		}
		else
		{
			charLine = (ASCII_24[charIndex][row * 2] & 0x00ff);
			charLine += (ASCII_24[charIndex][row * 2 + 1] & 0x00ff) << 8;
		}
			
		for (uint8_t col = 0; col < colSize; col++)
		{
			if (charLine & PointMask)
			{
				DrawPoint(x + col, y + row, color);
			}
			else if (NotMultiply == mode)
			{ 
				DrawPoint(x + col, y + row, defBackgroundColor);
			}

			charLine >>= 1;
				
			if ((x + col) >= fbdev->device.width) return;
		}

		if ((y + row) >= fbdev->device.height) return;
	}
}


/// @brief Display show string
/// @param x 
/// @param y 
/// @param str 
/// @param fontSize 
/// @param mode 
/// @param color 
void Display::ShowString(uint32_t x, uint32_t y, uint8_t* str, FontSize fontSize, DisplayMode mode, uint32_t color)
{
	uint32_t xOffset = x;
	uint32_t yOffset = y;

	while ((*str <= '~') && (*str >= ' '))
	{
		ShowChar(xOffset, yOffset, *str, fontSize, mode, color);

		xOffset += fontSize >> 1;

		if (xOffset > fbdev->device.width)
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		str++;
	}
}


/// @brief Display show string without x and y
/// @param str 
/// @param fontSize 
/// @param mode 
/// @param color 
void Display::ShowString(uint8_t* str, FontSize fontSize, DisplayMode mode, uint32_t color)
{
	static uint32_t xOffset = 0;
	static uint32_t yOffset = 0;

	while ('\0' != *str)
	{
		if ((xOffset + (fontSize >> 1) > fbdev->device.width) || ('\n' == *str))
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		if (yOffset + fontSize > fbdev->device.height)
		{
			uint32_t y0 = (yOffset + fontSize) - fbdev->device.height;
			for (uint32_t y = y0; y < fbdev->device.height; y++)
			{
				for (uint32_t x = 0; x < fbdev->device.width; x++)
				{
					uint32_t color = ReadPoint(x, y);
					DrawPoint(x, y - y0, color);
				}
			}

			xOffset = 0;
			yOffset = fbdev->device.height - fontSize;
			
			for (uint32_t y = yOffset; y < fbdev->device.height; y++)
			{
				for (uint32_t x = 0; x < fbdev->device.width; x++)
				{
					DrawPoint(x, y, defBackgroundColor);
				}
			}
		}

		if ((*str <= '~') && (*str >= ' '))
		{
			ShowChar(xOffset, yOffset, *str, fontSize, mode, color);

			xOffset += fontSize >> 1;
		}

		str++;
	}
}


/// @brief Display show picture
/// @param picture 
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void Display::ShowPicture(uint8_t *picture, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0)
	{
		width = (*(picture + 2) << 8) + *(picture + 3);
		height = (*(picture + 4) << 8) + *(picture + 5);
		picture += 8;
	}

	for (uint32_t yOffset = 0; yOffset < height; yOffset++)
	{
		for (uint32_t xOffset = 0; xOffset < width; xOffset++)
		{
			if (x + xOffset < fbdev->device.width && y + yOffset < fbdev->device.height)
			{
				DrawPoint(x + xOffset, y + yOffset, (*picture << 8) + *(picture + 1));
			}
			picture += 2;
		}
	}
}


/// @brief Printf
/// @param format 
/// @param  
void Display::Printf(const char* format, ...)
{
	lock.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	ShowString((uint8_t*)data);
	lock.Unlock();
}
