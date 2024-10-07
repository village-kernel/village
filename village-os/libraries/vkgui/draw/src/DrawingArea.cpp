//###########################################################################
// DrawingArea.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display draw area
/// @param area 
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void Drawing::DrawingArea(int *area, int x, int y, int width, int height)
{
	int index = 0;

	for (int yOffset = 0; yOffset < height; yOffset++)
	{
		for (int xOffset = 0; xOffset < width; xOffset++)
		{
			if (((x + xOffset) < limitX) && ((y + yOffset) < limitY))
			{
				DrawingPoint(x + xOffset, y + yOffset, area[index]);
			}
			index++;
		}
	}
}
