//###########################################################################
// vg_draw_buff.cpp
// Definitions of the functions that manage draw buff
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_buff.h"


/// @brief DrawBuff Initiate
/// @param devices 
void DrawBuff::Initiate(GraphicsDevices* devices)
{
	this->devices = devices;
}


/// @brief DrawBuff Execute
/// @param devices 
/// @param layerArea 
/// @param drawArea 
/// @param color 
void DrawBuff::Execute(DrawArea layerArea, DrawArea drawArea, int* buff)
{
	int maxX = devices->lcddev->GetWidth() - 1;
	int maxY = devices->lcddev->GetHeight() - 1;
	int sx = math.Sat(math.Max(drawArea.sx, layerArea.sx), 0, maxX);
	int ex = math.Sat(math.Min(drawArea.ex, layerArea.ex), 0, maxX);
	int sy = math.Sat(math.Max(drawArea.sy, layerArea.sy), 0, maxY);
	int ey = math.Sat(math.Min(drawArea.ey, layerArea.ey), 0, maxY);
	int lx = layerArea.sx;
	int ly = layerArea.sy;
	int len = layerArea.ex - layerArea.sx + 1;

	for (int x = sx; x <= ex; x++)
	{
		for (int y = sy; y <= ey; y++)
		{
			int color = buff[(x - lx) + (y - ly) * len];

			devices->lcddev->Point(x, y, color);
		}
	}
}
