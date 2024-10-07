//###########################################################################
// DrawingPoint.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display draw point
/// @param x 
/// @param y 
/// @param color 
void Drawing::DrawingPoint(int x, int y, int color)
{
	if (NULL != fbdev)
	{
		fbdev->DrawPoint(x, y, color);
	}
}


/// @brief Display read point
/// @param x 
/// @param y 
/// @return 
int Drawing::ReadingPoint(int x, int y)
{
	if (NULL != fbdev)
	{
		return fbdev->ReadPoint(x, y);
	}
	return 0;
}


/// @brief Dislplay read and draw point
/// @param x 
/// @param y
/// @param color 
/// @return 
int Drawing::ReadDrawPoint(int x, int y, int color)
{
	int ret = 0;

	if (NULL != fbdev)
	{
		ret = fbdev->ReadPoint(x, y);
		fbdev->DrawPoint(x, y, color);
	}
	
	return ret;
}
