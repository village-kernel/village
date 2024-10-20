//###########################################################################
// DrawingPoint.cpp
// Definitions of the functions that manage drawing point
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingPoint.h"
#include "Drawing.h"


/// @brief Drawing point set
/// @param x 
/// @param y 
/// @param color 
void DrawingPoint::Set(int x, int y, int color)
{
	if (NULL != drawing->fbdev)
	{
		drawing->fbdev->DrawPoint(x, y, color);
	}
}


/// @brief Drawing point get
/// @param x 
/// @param y 
/// @return 
int DrawingPoint::Get(int x, int y)
{
	if (NULL != drawing->fbdev)
	{
		return drawing->fbdev->ReadPoint(x, y);
	}
	return 0;
}
