//###########################################################################
// DrawingChar.cpp
// Definitions of the functions that manage drawing char
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingChar.h"
#include "Drawing.h"
#include "ASCIIFont.h"


/// @brief drawing char set
/// @param x 
/// @param y 
/// @param chr 
/// @param fontSize 
/// @param mode 
/// @param color 
void DrawingChar::Set(int x, int y, char chr, DrawingDefs::FontSize fontSize, DrawingDefs::DrawingMode mode, int color)
{
	const uint16_t PointMask = 0x0001;

	uint16_t charLine = 0;
	uint16_t charIndex = chr - ' ';
	uint8_t rowSize = fontSize;
	uint8_t colSize = fontSize >> 1;

	for (uint8_t row = 0; row < rowSize; row++)
	{
		if (DrawingDefs::Font16 == fontSize)
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
				drawing->point.Set(x + col, y + row, color);
			}
			else if (DrawingDefs::NotMultiply == mode)
			{ 
				drawing->point.Set(x + col, y + row, DrawingDefs::defBgColor);
			}

			charLine >>= 1;
				
			if ((x + col) > limitX) return;
		}

		if ((y + row) > limitY) return;
	}
}
