//###########################################################################
// vg_draw_rect.cpp
// Definitions of the functions that manage draw rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_rect.h"


/// @brief Initiate
/// @param devices 
void DrawRect::Initiate(GraphicsDevices* devices)
{
	this->devices = devices;
}


/// @brief DrawRect Execute
/// @param devices 
/// @param layerArea 
/// @param drawArea 
/// @param color 
void DrawRect::Execute(DrawArea layerArea, DrawArea drawArea, int color)
{
	for (int x = layerArea.x0; x < layerArea.x1; x++)
	{
		if (!(x >= drawArea.x0 && x <= drawArea.x1)) continue;

		for (int y = layerArea.y0; y < layerArea.y1; y++)
		{
			if (!(y >= drawArea.y0 && y <= drawArea.y1)) continue;

			devices->lcddev->Point(x, y, color);
		}
	}
}
