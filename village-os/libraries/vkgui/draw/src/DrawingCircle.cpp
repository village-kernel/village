//###########################################################################
// DrawingCircle.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display draw circle
/// @param x 
/// @param y 
/// @param r 
/// @param color 
void Drawing::DrawingCircle(int x, int y, int r, int* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		if (colors != NULL)
		{
			DrawingPoint(x + xOffset, y - yOffset, colors[index++]);             //5
			DrawingPoint(x + yOffset, y - xOffset, colors[index++]);             //0
			DrawingPoint(x + yOffset, y + xOffset, colors[index++]);             //4
			DrawingPoint(x + xOffset, y + yOffset, colors[index++]);             //6
			DrawingPoint(x - xOffset, y + yOffset, colors[index++]);             //1
			DrawingPoint(x - yOffset, y + xOffset, colors[index++]);             //3
			DrawingPoint(x - xOffset, y - yOffset, colors[index++]);             //2
			DrawingPoint(x - yOffset, y - xOffset, colors[index++]);             //7
		}
		else
		{
			DrawingPoint(x + xOffset, y - yOffset, defStrokeColor);             //5
			DrawingPoint(x + yOffset, y - xOffset, defStrokeColor);             //0
			DrawingPoint(x + yOffset, y + xOffset, defStrokeColor);             //4
			DrawingPoint(x + xOffset, y + yOffset, defStrokeColor);             //6
			DrawingPoint(x - xOffset, y + yOffset, defStrokeColor);             //1
			DrawingPoint(x - yOffset, y + xOffset, defStrokeColor);             //3
			DrawingPoint(x - xOffset, y - yOffset, defStrokeColor);             //2
			DrawingPoint(x - yOffset, y - xOffset, defStrokeColor);             //7
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
void Drawing::ReadingCircle(int x, int y, int r, int* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		colors[index++] = ReadingPoint(x + xOffset, y - yOffset);             //5
		colors[index++] = ReadingPoint(x + yOffset, y - xOffset);             //0
		colors[index++] = ReadingPoint(x + yOffset, y + xOffset);             //4
		colors[index++] = ReadingPoint(x + xOffset, y + yOffset);             //6
		colors[index++] = ReadingPoint(x - xOffset, y + yOffset);             //1
		colors[index++] = ReadingPoint(x - yOffset, y + xOffset);             //3
		colors[index++] = ReadingPoint(x - xOffset, y - yOffset);             //2
		colors[index++] = ReadingPoint(x - yOffset, y - xOffset);             //7
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
