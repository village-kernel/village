//###########################################################################
// DrawingString.cpp
// Definitions of the functions that manage drawing string
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingString.h"
#include "Drawing.h"
#include "ASCIIFont.h"


/// @brief Drawing string set
/// @param x 
/// @param y 
/// @param str 
/// @param fontSize 
/// @param mode 
/// @param color 
void DrawingString::Set(int x, int y, char* str, DrawingDefs::FontSize fontSize, DrawingDefs::DrawingMode mode, int color)
{
	int xOffset = x;
	int yOffset = y;

	if (NULL != str)
	{
		while ((*str <= '~') && (*str >= ' '))
		{
			drawing->chr.Set(xOffset, yOffset, *str, fontSize, mode, color);

			xOffset += fontSize >> 1;

			if (xOffset > limitX)
			{
				xOffset = 0;
				yOffset += fontSize;
			}

			str++;
		}
	}
}
