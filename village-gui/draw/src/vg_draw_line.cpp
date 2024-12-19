//###########################################################################
// vg_draw_line.cpp
// Definitions of the functions that manage draw line
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_line.h"


/// @brief Initiate
/// @param devices 
void DrawLine::Initiate(VgDevices* devices)
{
	this->devices = devices;
}


/// @brief Draw line set
/// @param layerArea 
/// @param drawArea 
/// @param color 
void DrawLine::Execute(DrawArea layerArea, DrawArea drawArea, int color)
{
	int xError = 0, yError = 0, distance = 0;
	int xIncrease = 0, yIncrease = 0;
	
	int xDelta = layerArea.ex - layerArea.sx;
	int yDelta = layerArea.ey - layerArea.sy;
	int pointX = layerArea.sx;
	int pointY = layerArea.sy;
	
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

	for (int i = 0; i <= (distance + 1); i++)
	{
		devices->lcddev->Point(pointX, pointY, color);
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
