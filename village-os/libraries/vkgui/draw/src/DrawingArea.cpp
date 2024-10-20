//###########################################################################
// DrawingArea.cpp
// Definitions of the functions that manage drawing area
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingArea.h"
#include "Drawing.h"


/// @brief Drawing area set
/// @param area 
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void DrawingArea::Set(int x, int y, int width, int height, int *area)
{
	int index = 0;

	for (int yOffset = 0; yOffset < height; yOffset++)
	{
		for (int xOffset = 0; xOffset < width; xOffset++)
		{
			if (((x + xOffset) < limitX) && ((y + yOffset) < limitY))
			{
				drawing->point.Set(x + xOffset, y + yOffset, area[index]);
			}
			index++;
		}
	}
}


/// @brief Drawing area get
/// @param area 
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void DrawingArea::Get(int x, int y, int width, int height, int *area)
{
	int index = 0;

	for (int yOffset = 0; yOffset < height; yOffset++)
	{
		for (int xOffset = 0; xOffset < width; xOffset++)
		{
			if (((x + xOffset) < limitX) && ((y + yOffset) < limitY))
			{
				area[index] = drawing->point.Get(x + xOffset, y + yOffset);
			}
			index++;
		}
	}
}
