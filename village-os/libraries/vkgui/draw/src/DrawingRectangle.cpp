//###########################################################################
// DrawingRectangle.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"


/// @brief Display draw rectangle
/// @param x0 
/// @param y0 
/// @param x1 
/// @param y1 
/// @param color 
void Drawing::DrawingRectangle(int x0, int y0, int x1, int y1, int color)
{
	DrawingLine(x0, y0, x1, y0, color);
	DrawingLine(x0, y0, x0, y1, color);
	DrawingLine(x0, y1, x1, y1, color);
	DrawingLine(x1, y0, x1, y1, color);
}
