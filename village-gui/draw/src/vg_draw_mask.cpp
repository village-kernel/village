//###########################################################################
// vg_draw_mask.cpp
// Definitions of the functions that manage draw mask
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_draw_mask.h"


/// @brief Initiate
/// @param devices 
void DrawMask::Initiate(GraphicsDevices* devices)
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
	
	lineArea.x0 = layerArea.x0;
	lineArea.x1 = layerArea.x1;
	lineArea.y0 = layerArea.y0;
	lineArea.y1 = layerArea.y0;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.x0 = layerArea.x0;
	lineArea.x1 = layerArea.x0;
	lineArea.y0 = layerArea.y0;
	lineArea.y1 = layerArea.y1;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.x0 = layerArea.x0;
	lineArea.x1 = layerArea.x1;
	lineArea.y0 = layerArea.y1;
	lineArea.y1 = layerArea.y1;
	line.Execute(lineArea, drawArea, color);
	
	lineArea.x0 = layerArea.x1;
	lineArea.x1 = layerArea.x1;
	lineArea.y0 = layerArea.y0;
	lineArea.y1 = layerArea.y1;
	line.Execute(lineArea, drawArea, color);
}
