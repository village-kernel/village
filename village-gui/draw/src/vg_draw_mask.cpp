//###########################################################################
// vg_draw_mask.cpp
// Definitions of the functions that manage draw mask
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_mask.h"


/// @brief Initiate
/// @param devices 
void DrawMask::Initiate(VgDevices* devices)
{
	this->devices = devices;

	line.Initiate(devices);
}


/// @brief Draw mask
/// @param layerArea 
/// @param drawArea 
/// @param color 
void DrawMask::Execute(DrawArea layerArea, DrawArea drawArea, int color)
{
	DrawArea lineArea;
	
	lineArea.sx = layerArea.sx;
	lineArea.ex = layerArea.ex;
	lineArea.sy = layerArea.sy;
	lineArea.ey = layerArea.sy;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.sx = layerArea.sx;
	lineArea.ex = layerArea.sx;
	lineArea.sy = layerArea.sy;
	lineArea.ey = layerArea.ey;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.sx = layerArea.sx;
	lineArea.ex = layerArea.ex;
	lineArea.sy = layerArea.ey;
	lineArea.ey = layerArea.ey;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.sx = layerArea.ex;
	lineArea.ex = layerArea.ex;
	lineArea.sy = layerArea.sy;
	lineArea.ey = layerArea.ey;
	line.Execute(lineArea, drawArea, color);
}
