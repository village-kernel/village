//###########################################################################
// vg_draw_rect.cpp
// Definitions of the functions that manage draw rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_rect.h"


/// @brief DrawRect Execute
/// @param data 
void DrawRect::Execute(DrawArea layerArea, DrawArea drawArea, int color)
{
	int pixelsize = (drawArea.x1 - drawArea.x0) * (drawArea.y1 - drawArea.y0);
	uint16_t* pixels = new uint16_t[pixelsize]();

	for (uint16_t i = 0; i < pixelsize; i++)
	{
		pixels[i] = color;
	}

	delete[] (uint16_t*)Output.pixels;
	Output.area = drawArea;
	Output.pixels = pixels;
}
