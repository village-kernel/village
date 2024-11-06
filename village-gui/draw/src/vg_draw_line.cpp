//###########################################################################
// vg_draw_line.cpp
// Definitions of the functions that manage draw line
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_line.h"


/// @brief Draw line set
/// @param x0 
/// @param y0 
/// @param x1 
/// @param y1 
/// @param color 
void DrawLine::Execute(int x0, int y0, int x1, int y1, int color)
{
	//int xError = 0, yError = 0, distance = 0;
	//int xIncrease = 0, yIncrease = 0;
	
	//int xDelta = x1 - x0;
	//int yDelta = y1 - y0;
	//int pointX = x0;
	//int pointY = y0;
	
	//if (xDelta > 0)
	//{
	//	xIncrease = 1;
	//}
	//else if (xDelta == 0)
	//{
	//	xIncrease = 0;
	//}
	//else
	//{
	//	xIncrease = -1;
	//	xDelta = -xDelta; 
	//}

	//if (yDelta > 0)
	//{
	//	yIncrease = 1;
	//}
	//else if (yDelta == 0)
	//{
	//	yIncrease = 0;
	//}
	//else
	//{
	//	yIncrease = -1;
	//	yDelta = -yDelta; 
	//}

	//if (xDelta > yDelta)
	//{
	//	distance = xDelta;
	//}
	//else
	//{
	//	distance = yDelta;
	//}

	//for (int i = 0; i <= (distance + 1); i++)
	//{
	//	draw->point.Set(pointX, pointY, color);
	//	xError += xDelta;
	//	yError += yDelta;
	//	if (xError > distance)
	//	{
	//		xError -= distance;
	//		pointX += xIncrease;
	//	}
	//	if (yError > distance)
	//	{
	//		yError -= distance;
	//		pointY += yIncrease;
	//	}
	//}
}
