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
/// @param font 
/// @param mode 
/// @param color 
void DrawingString::Set(int x, int y, char* str, int font, int mode, int color)
{
	int xOffset = x;
	int yOffset = y;

	if (NULL != str)
	{
		while ((*str <= '~') && (*str >= ' '))
		{
			drawing->chr.Set(xOffset, yOffset, *str, font, mode, color);

			xOffset += font >> 1;

			if (xOffset > limitX)
			{
				xOffset = 0;
				yOffset += font;
			}

			str++;
		}
	}
}
