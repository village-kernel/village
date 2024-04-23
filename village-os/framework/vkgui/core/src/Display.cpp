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
	:limitX(0),
	limitY(0)
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
	limitX = fbdev->device.width - 1;
	limitY = fbdev->device.height - 1;
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


/// @brief Dislplay read and draw point
/// @param x 
/// @param y
/// @param color 
/// @return 
uint32_t Display::ReadDrawPoint(uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t ret = fbdev->ReadPoint(x, y);
	fbdev->DrawPoint(x, y, color);
	return ret;
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
void Display::DrawCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		if (colors != NULL)
		{
			DrawPoint(x + xOffset, y - yOffset, colors[index++]);             //5
			DrawPoint(x + yOffset, y - xOffset, colors[index++]);             //0
			DrawPoint(x + yOffset, y + xOffset, colors[index++]);             //4
			DrawPoint(x + xOffset, y + yOffset, colors[index++]);             //6
			DrawPoint(x - xOffset, y + yOffset, colors[index++]);             //1
			DrawPoint(x - yOffset, y + xOffset, colors[index++]);             //3
			DrawPoint(x - xOffset, y - yOffset, colors[index++]);             //2
			DrawPoint(x - yOffset, y - xOffset, colors[index++]);             //7
		}
		else
		{
			DrawPoint(x + xOffset, y - yOffset, defStrokeColor);             //5
			DrawPoint(x + yOffset, y - xOffset, defStrokeColor);             //0
			DrawPoint(x + yOffset, y + xOffset, defStrokeColor);             //4
			DrawPoint(x + xOffset, y + yOffset, defStrokeColor);             //6
			DrawPoint(x - xOffset, y + yOffset, defStrokeColor);             //1
			DrawPoint(x - yOffset, y + xOffset, defStrokeColor);             //3
			DrawPoint(x - xOffset, y - yOffset, defStrokeColor);             //2
			DrawPoint(x - yOffset, y - xOffset, defStrokeColor);             //7
		}

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


/// @brief Display read circle
/// @param x 
/// @param y 
/// @param r 
/// @param color 
void Display::ReadCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		colors[index++] = ReadPoint(x + xOffset, y - yOffset);             //5
		colors[index++] = ReadPoint(x + yOffset, y - xOffset);             //0
		colors[index++] = ReadPoint(x + yOffset, y + xOffset);             //4
		colors[index++] = ReadPoint(x + xOffset, y + yOffset);             //6
		colors[index++] = ReadPoint(x - xOffset, y + yOffset);             //1
		colors[index++] = ReadPoint(x - yOffset, y + xOffset);             //3
		colors[index++] = ReadPoint(x - xOffset, y - yOffset);             //2
		colors[index++] = ReadPoint(x - yOffset, y - xOffset);             //7
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
				
			if ((x + col) > limitX) return;
		}

		if ((y + row) > limitY) return;
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

		if (xOffset > limitX)
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
		if ((xOffset + (fontSize >> 1) > limitX) || ('\n' == *str))
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		if (yOffset + fontSize > limitY)
		{
			uint32_t y0 = (yOffset + fontSize) - limitY;
			for (uint32_t y = y0; y < limitY; y++)
			{
				for (uint32_t x = 0; x < limitX; x++)
				{
					uint32_t color = ReadPoint(x, y);
					DrawPoint(x, y - y0, color);
				}
			}

			xOffset = 0;
			yOffset = limitY - fontSize;
			
			for (uint32_t y = yOffset; y < limitY; y++)
			{
				for (uint32_t x = 0; x < limitX; x++)
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


/// @brief Display show area
/// @param area 
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void Display::ShowArea(uint32_t *area, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	uint32_t index = 0;

	for (uint32_t yOffset = 0; yOffset < height; yOffset++)
	{
		for (uint32_t xOffset = 0; xOffset < width; xOffset++)
		{
			if (((x + xOffset) < limitX) && ((y + yOffset) < limitY))
			{
				DrawPoint(x + xOffset, y + yOffset, area[index]);
			}
			index++;
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
