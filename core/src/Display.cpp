//###########################################################################
// Dispaly.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Display.h"


///Constructor
Display::Display()
{
}


///Display Initialize
void Display::Initialize(VirtualDisp* disp)
{
	this->disp = disp;
}


///Display open window
void Display::OpenWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	disp->OpenWindow(x, y, width, height);
}


///Display set cursor
void Display::SetCursor(uint16_t x, uint16_t y)
{
	disp->SetCursor(x, y);
}


///Display fill color
void Display::Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	disp->Fill(x0, y0, x1, y1, color);
}


///Display clear
void Display::Clear(uint16_t color)
{
	disp->Clear(color);
}


///Display draw point
void Display::DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	disp->DrawPoint(x, y, color);
}


///Display read point
uint16_t Display::ReadPoint(uint16_t x, uint16_t y)
{
	return disp->ReadPoint(x, y);
}


///Display draw line
void Display::DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int xError = 0, yError = 0, distance = 0;
	int xIncrease = 0, yIncrease = 0;
	
	int xDelta = x1 - x0;
	int yDelta = y1 - y0;
	int pointX = x0;
	int pointY = y0;
	
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

	for (uint16_t point = 0; point <= distance + 1; point++)
	{
		DrawPoint(pointX, pointY);
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


///Display draw rectangle
void Display::DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	DrawLine(x0, y0, x1, y0);
	DrawLine(x0, y0, x0, y1);
	DrawLine(x0, y1, x1, y1);
	DrawLine(x1, y0, x1, y1);
}


///Display draw circle
void Display::DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);

	while (xOffset <= yOffset)
	{
		DrawPoint(x + xOffset, y - yOffset);             //5
		DrawPoint(x + yOffset, y - xOffset);             //0           
		DrawPoint(x + yOffset, y + xOffset);             //4               
		DrawPoint(x + xOffset, y + yOffset);             //6 
		DrawPoint(x - xOffset, y + yOffset);             //1       
		DrawPoint(x - yOffset, y + xOffset);             //3
		DrawPoint(x - xOffset, y - yOffset);             //2             
		DrawPoint(x - yOffset, y - xOffset);             //7     	         
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


///Display show char
void Display::ShowChar(uint16_t x, uint16_t y, uint8_t charVal, FontSize fontSize, DisplayMode mode, uint16_t color)
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
				
			if ((x + col) >= disp->device.width) return;
		}

		if ((y + row) >= disp->device.height) return;
	}
}


///Display show string
void Display::ShowString(uint16_t x, uint16_t y, uint8_t* str, FontSize fontSize, DisplayMode mode, uint16_t color)
{
	uint16_t xOffset = x;
	uint16_t yOffset = y;

	while ((*str <= '~') && (*str >= ' '))
	{
		ShowChar(xOffset, yOffset, *str, fontSize, mode, color);

		xOffset += fontSize >> 1;

		if (xOffset > disp->device.width)
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		str++;
	}
}


///Display show string without x and y
void Display::ShowString(uint8_t* str, FontSize fontSize, DisplayMode mode, uint16_t color)
{
	static uint16_t xOffset = 0;
	static uint16_t yOffset = 0;

	while ('\0' != *str)
	{
		if ((xOffset >= disp->device.width) || ('\n' == *str))
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		if (yOffset >= disp->device.height)
		{
			xOffset = 0;
			yOffset = 0;
			Clear();
		}

		if ((*str <= '~') && (*str >= ' '))
		{
			ShowChar(xOffset, yOffset, *str, fontSize, mode, color);

			xOffset += fontSize >> 1;
		}

		str++;
	}
}


///Display show picture
void Display::ShowPicture(uint8_t *picture, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	if (width == 0 || height == 0)
	{
		width = (*(picture + 2) << 8) + *(picture + 3);
		height = (*(picture + 4) << 8) + *(picture + 5);
		picture += 8;
	}

	for (uint16_t yOffset = 0; yOffset < height; yOffset++)
	{
		for (uint16_t xOffset = 0; xOffset < width; xOffset++)
		{
			if (x + xOffset < disp->device.width && y + yOffset < disp->device.height)
			{
				DrawPoint(x + xOffset, y + yOffset, (*picture << 8) + *(picture + 1));
			}
			picture += 2;
		}
	}
}

