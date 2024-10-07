//###########################################################################
// DrawingCircle.cpp
// Definitions of the functions that manage drawing circle
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingCircle.h"
#include "Drawing.h"


/// @brief Drawing circle
/// @param x 
/// @param y 
/// @param r 
/// @param color 
void DrawingCircle::Set(int x, int y, int r, int* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		if (colors != NULL)
		{
			drawing->point.Set(x + xOffset, y - yOffset, colors[index++]);             //5
			drawing->point.Set(x + yOffset, y - xOffset, colors[index++]);             //0
			drawing->point.Set(x + yOffset, y + xOffset, colors[index++]);             //4
			drawing->point.Set(x + xOffset, y + yOffset, colors[index++]);             //6
			drawing->point.Set(x - xOffset, y + yOffset, colors[index++]);             //1
			drawing->point.Set(x - yOffset, y + xOffset, colors[index++]);             //3
			drawing->point.Set(x - xOffset, y - yOffset, colors[index++]);             //2
			drawing->point.Set(x - yOffset, y - xOffset, colors[index++]);             //7
		}
		else
		{
			drawing->point.Set(x + xOffset, y - yOffset, DrawingDefs::defStrokeColor);             //5
			drawing->point.Set(x + yOffset, y - xOffset, DrawingDefs::defStrokeColor);             //0
			drawing->point.Set(x + yOffset, y + xOffset, DrawingDefs::defStrokeColor);             //4
			drawing->point.Set(x + xOffset, y + yOffset, DrawingDefs::defStrokeColor);             //6
			drawing->point.Set(x - xOffset, y + yOffset, DrawingDefs::defStrokeColor);             //1
			drawing->point.Set(x - yOffset, y + xOffset, DrawingDefs::defStrokeColor);             //3
			drawing->point.Set(x - xOffset, y - yOffset, DrawingDefs::defStrokeColor);             //2
			drawing->point.Set(x - yOffset, y - xOffset, DrawingDefs::defStrokeColor);             //7
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
void DrawingCircle::Get(int x, int y, int r, int* colors)
{
	int xOffset = 0;
	int yOffset = r;
	int nextPoint = 3 - (r << 1);
	int index = 0;

	while (xOffset <= yOffset)
	{
		colors[index++] = drawing->point.Get(x + xOffset, y - yOffset);             //5
		colors[index++] = drawing->point.Get(x + yOffset, y - xOffset);             //0
		colors[index++] = drawing->point.Get(x + yOffset, y + xOffset);             //4
		colors[index++] = drawing->point.Get(x + xOffset, y + yOffset);             //6
		colors[index++] = drawing->point.Get(x - xOffset, y + yOffset);             //1
		colors[index++] = drawing->point.Get(x - yOffset, y + xOffset);             //3
		colors[index++] = drawing->point.Get(x - xOffset, y - yOffset);             //2
		colors[index++] = drawing->point.Get(x - yOffset, y - xOffset);             //7
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
