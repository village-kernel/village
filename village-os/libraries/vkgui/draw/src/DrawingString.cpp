//###########################################################################
// DrawingString.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display show string
/// @param x 
/// @param y 
/// @param str 
/// @param fontSize 
/// @param mode 
/// @param color 
void Drawing::DrawingString(int x, int y, char* str, FontSize fontSize, DisplayMode mode, int color)
{
	int xOffset = x;
	int yOffset = y;

	if (NULL != str)
	{
		while ((*str <= '~') && (*str >= ' '))
		{
			DrawingChar(xOffset, yOffset, *str, fontSize, mode, color);

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


/// @brief Display show string without x and y
/// @param str 
/// @param fontSize 
/// @param mode 
/// @param color 
void Drawing::DrawingString(char* str, FontSize fontSize, DisplayMode mode, int color)
{
	static int xOffset = 0;
	static int yOffset = 0;

	while ('\0' != *str)
	{
		if ((xOffset + (fontSize >> 1) > limitX) || ('\n' == *str))
		{
			xOffset = 0;
			yOffset += fontSize;
		}

		if (yOffset + fontSize > limitY)
		{
			int y0 = (yOffset + fontSize) - limitY;
			for (int y = y0; y < limitY; y++)
			{
				for (int x = 0; x < limitX; x++)
				{
					int color = ReadingPoint(x, y);
					DrawingPoint(x, y - y0, color);
				}
			}

			xOffset = 0;
			yOffset = limitY - fontSize;
			
			for (int y = yOffset; y < limitY; y++)
			{
				for (int x = 0; x < limitX; x++)
				{
					DrawingPoint(x, y, defBackgroundColor);
				}
			}
		}

		if ((*str <= '~') && (*str >= ' '))
		{
			DrawingChar(xOffset, yOffset, *str, fontSize, mode, color);

			xOffset += fontSize >> 1;
		}

		str++;
	}
}
