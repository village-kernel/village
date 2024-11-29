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
	int x0 = math.Sat(math.Max(drawArea.x0, layerArea.x0), 0, maxX);
	int x1 = math.Sat(math.Min(drawArea.x1, layerArea.x1), 0, maxX);
	int y0 = math.Sat(math.Max(drawArea.y0, layerArea.y0), 0, maxY);
	int y1 = math.Sat(math.Min(drawArea.y1, layerArea.y1), 0, maxY);
	int lx = layerArea.x0;
	int ly = layerArea.y0;
	int len = layerArea.x1 - layerArea.x0 + 1;

	for (int x = x0; x <= x1; x++)
	{
		for (int y = y0; y <= y1; y++)
		{
			int color = buff[(x - lx) + (y - ly) * len];

			devices->lcddev->Point(x, y, color);
		}
	}
}
