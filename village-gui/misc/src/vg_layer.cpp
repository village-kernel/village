//###########################################################################
// vg_layer.cpp
// Definitions of the functions that manage layer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_layer.h"


/// @brief Constructor
Layer::Layer()
{
}


/// @brief Destructor
Layer::~Layer()
{
}


/// @brief Layer is coordinate in the area
/// @param x 
/// @param y 
/// @param area 
/// @return 
bool Layer::IsCoordinateInArea(int x, int y, DrawArea area)
{
	return ((x >= area.x0 && x <= area.x1) && 
			(y >= area.y0 && y <= area.y1));
}


/// @brief Layer is area overlap
/// @param a0 
/// @param a1 
/// @return 
bool Layer::IsAreaOverlap(DrawArea a0, DrawArea a1)
{
	if (IsCoordinateInArea(a0.x0, a0.y0, a1)) return true;
	if (IsCoordinateInArea(a0.x0, a0.y1, a1)) return true;
	if (IsCoordinateInArea(a0.x1, a0.y0, a1)) return true;
	if (IsCoordinateInArea(a0.x1, a0.y1, a1)) return true;
	return false;
}


/// @brief Layer get the overlap area
/// @param a0 
/// @param a1 
/// @return 
DrawArea Layer::GetOverlapArea(DrawArea a0, DrawArea a1)
{
	DrawArea a;

	a.x0 = math.Max(a0.x0, a1.x0); 
	a.x1 = math.Min(a0.x1, a1.x1);
	a.y0 = math.Max(a0.y0, a1.y0);
	a.y1 = math.Min(a0.y1, a1.y1);

	return a;
}


/// @brief Layer cut the overlap area
/// @param a0 
/// @param a1 
/// @return 
DrawArea Layer::CutOverlapArea(DrawArea a0, DrawArea a1)
{
	DrawArea a = a0;
	
	if (a0.y0 >= a1.y0 && a0.y1 <= a1.y1)
	{
		if (a0.x0 >= a1.x0 && a0.x0 < a1.x1 && a0.x1 > a1.x1)
			a.x0 = a1.x1;
		if (a0.x1 > a1.x0 && a0.x1 <= a1.x1 && a0.x0 < a1.x0)
			a.x1 = a1.x0;
	}

	if (a0.x0 >= a1.x0 && a0.x1 <= a1.x1)
	{
		if (a0.y0 >= a1.y0 && a0.y0 < a1.y1 && a0.y1 > a1.y1)
			a.y0 = a1.y1;
		if (a0.y1 > a1.y0 && a0.y1 <= a1.y1 && a0.y0 < a1.y0)
			a.y1 = a1.y0;	
	}

	return a;
}


/// @brief Layer incise the overlap area
/// @param a0 
/// @param a1 
/// @return 
List<DrawArea> Layer::InciseOverlapArea(DrawArea a0, DrawArea a1)
{
	List<DrawArea> list;
	
	//Upper
	if (a0.y0 < a1.y0)
	{
		DrawArea a;
		a.x0 = a0.x0;
		a.x1 = a0.x1;
		a.y0 = a0.y0;
		a.y1 = a1.y0;
		list.Add(a);
	}

	//Under
	if (a0.y1 > a1.y1)
	{
		DrawArea a;
		a.x0 = a0.x0;
		a.x1 = a0.x1;
		a.y0 = a1.y1;
		a.y1 = a0.y1;
		list.Add(a);
	}

	//Left
	if (a0.x0 < a1.x0)
	{
		DrawArea a;
		a.x0 = a0.x0;
		a.x1 = a1.x0;
		a.y0 = math.Max(a0.y0, a1.y0);
		a.y1 = math.Min(a0.y1, a1.y1);
		list.Add(a);
	}

	//Right
	if (a0.x1 > a1.x1)
	{
		DrawArea a;
		a.x0 = a1.x1;
		a.x1 = a0.x1;
		a.y0 = math.Max(a0.y0, a1.y0);
		a.y1 = math.Min(a0.y1, a1.y1);
		list.Add(a);
	}

	return list;
}


/// @brief Layer moved the overlap area
/// @param oldArea 
/// @param newArea 
/// @return 
List<DrawArea> Layer::MovedOverlapArea(DrawArea oldArea, DrawArea newArea)
{
	List<DrawArea> list;

	if (IsAreaOverlap(oldArea, newArea))
		list = InciseOverlapArea(oldArea, newArea);
	else
		list.Add(oldArea);

	return list;
}
