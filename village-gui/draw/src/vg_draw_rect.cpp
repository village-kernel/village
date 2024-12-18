//###########################################################################
// vg_draw_rect.cpp
// Definitions of the functions that manage draw rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_rect.h"


/// @brief DrawRect Initiate
/// @param devices 
void DrawRect::Initiate(VgDevices* devices)
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
	int maxX = devices->lcddev->GetWidth() - 1;
	int maxY = devices->lcddev->GetHeight() - 1;
	int sx = math.Sat(math.Max(drawArea.sx, layerArea.sx), 0, maxX);
	int ex = math.Sat(math.Min(drawArea.ex, layerArea.ex), 0, maxX);
	int sy = math.Sat(math.Max(drawArea.sy, layerArea.sy), 0, maxY);
	int ey = math.Sat(math.Min(drawArea.ey, layerArea.ey), 0, maxY);

	for (int y = sy; y <= ey; y++)
	{
		for (int x = sx; x <= ex; x++)
		{
			devices->lcddev->Point(x, y, color);
		}
	}
}
