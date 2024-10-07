//###########################################################################
// DrawingRect.cpp
// Definitions of the functions that manage drawing rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingRect.h"
#include "Drawing.h"


/// @brief Drawing rect set
/// @param x0 
/// @param y0 
/// @param x1 
/// @param y1 
/// @param color 
void DrawingRect::Set(int x0, int y0, int x1, int y1, int color)
{
	drawing->line.Set(x0, y0, x1, y0, color);
	drawing->line.Set(x0, y0, x0, y1, color);
	drawing->line.Set(x0, y1, x1, y1, color);
	drawing->line.Set(x1, y0, x1, y1, color);
}
