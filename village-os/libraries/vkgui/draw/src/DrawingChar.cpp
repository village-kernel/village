//###########################################################################
// DrawingChar.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display draw char
/// @param x 
/// @param y 
/// @param charVal 
/// @param fontSize 
/// @param mode 
/// @param color 
void Drawing::DrawingChar(int x, int y, char charVal, FontSize fontSize, DisplayMode mode, int color)
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
			charLine  = (ASCII_24[charIndex][row * 2 + 0] & 0x00ff) << 0;
			charLine += (ASCII_24[charIndex][row * 2 + 1] & 0x00ff) << 8;
		}
			
		for (uint8_t col = 0; col < colSize; col++)
		{
			if (charLine & PointMask)
			{
				DrawingPoint(x + col, y + row, color);
			}
			else if (NotMultiply == mode)
			{ 
				DrawingPoint(x + col, y + row, defBackgroundColor);
			}

			charLine >>= 1;
				
			if ((x + col) > limitX) return;
		}

		if ((y + row) > limitY) return;
	}
}
