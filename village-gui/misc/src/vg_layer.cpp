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
	return ((x >= area.sx && x <= area.ex) && 
			(y >= area.sy && y <= area.ey));
}


/// @brief Layer is area overlap
/// @param a0 
/// @param a1 
/// @return 
bool Layer::IsAreaOverlap(DrawArea a0, DrawArea a1)
{
	if (IsCoordinateInArea(a0.sx, a0.sy, a1)) return true;
	if (IsCoordinateInArea(a0.sx, a0.ey, a1)) return true;
	if (IsCoordinateInArea(a0.ex, a0.sy, a1)) return true;
	if (IsCoordinateInArea(a0.ex, a0.ey, a1)) return true;
	return false;
}


/// @brief Layer is area the same
/// @param a0 
/// @param a1 
/// @return 
bool Layer::IsAreaSame(DrawArea a0, DrawArea a1)
{
	return (a0.sx == a1.sx && a0.ex == a1.ex && 
			a0.sy == a1.sy && a0.ey == a1.ey);
}


/// @brief Layer is area valid
/// @param dsc 
/// @return 
bool Layer::IsAreaVaild(DrawArea dsc)
{
	return ((dsc.ex - dsc.sx) > 0 && (dsc.ey - dsc.sy) > 0);
}


/// @brief Layer get the overlap area
/// @param a0 
/// @param a1 
/// @return 
DrawArea Layer::GetOverlapArea(DrawArea a0, DrawArea a1)
{
	DrawArea a;

	a.sx = math.Max(a0.sx, a1.sx); 
	a.ex = math.Min(a0.ex, a1.ex);
	a.sy = math.Max(a0.sy, a1.sy);
	a.ey = math.Min(a0.ey, a1.ey);

	return a;
}


/// @brief Get overlap areas
/// @return 
DrawAreas Layer::GetOverlapAreas(DrawArea dsc, DrawAreas areas)
{
	DrawAreas getAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		if (IsAreaOverlap(dsc, area))
		{
			getAreas.Add(GetOverlapArea(dsc, area));
		}
	}

	return getAreas;
}


/// @brief Layer cut the overlap areas
/// @param a0 
/// @param a1 
/// @return 
DrawAreas Layer::CutOverlapAreas(DrawArea a0, DrawArea a1)
{
	DrawAreas list;

	//Not overlap
	if (!IsAreaOverlap(a0, a1))
	{
		list.Add(a0);
		return list;
	}

	//A1 shrinks by one pixel
	a1.sx = a1.sx - 1;
	a1.ex = a1.ex + 1;
	a1.sy = a1.sy - 1;
	a1.ey = a1.ey + 1;
	
	//Upper
	if (a0.sy <= a1.sy)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a0.sy;
		a.ey = a1.sy;
		list.Add(a);
	}

	//Under
	if (a0.ey >= a1.ey)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a1.ey;
		a.ey = a0.ey;
		list.Add(a);
	}

	//Left
	if (a0.sx <= a1.sx)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a1.sx;
		a.sy = math.Max(a0.sy, a1.sy);
		a.ey = math.Min(a0.ey, a1.ey);
		list.Add(a);
	}

	//Right
	if (a0.ex >= a1.ex)
	{
		DrawArea a;
		a.sx = a1.ex;
		a.ex = a0.ex;
		a.sy = math.Max(a0.sy, a1.sy);
		a.ey = math.Min(a0.ey, a1.ey);
		list.Add(a);
	}

	return list;
}


/// @brief Add area to areas
/// @param areas 
/// @param area 
/// @return 
DrawAreas Layer::AddAreaToAreas(DrawAreas areas, DrawArea area)
{
	DrawAreas appendAreas;

	appendAreas.Add(area);

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		appendAreas = CutAreaFromAreas(appendAreas, areas.Item());
	}

	areas.Append(appendAreas);

	return areas;
}


/// @brief Cut area from areas
/// @param areas 
/// @param area 
/// @return 
DrawAreas Layer::CutAreaFromAreas(DrawAreas areas, DrawArea area)
{
	DrawAreas cutAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		cutAreas.Append(CutOverlapAreas(areas.Item(), area));
	}

	return cutAreas;
}


/// @brief Calc overlap areas
/// @param dsc 
/// @param overlap 
/// @param upper 
/// @return 
DrawAreas Layer::CalcOverlapAreas(DrawArea dsc, DrawAreas overlapAreas, DrawAreas upperAreas)
{
	DrawAreas areas;

	DrawAreas overlaps = GetOverlapAreas(dsc, overlapAreas);
	
	for (overlaps.Begin(); !overlaps.IsEnd(); overlaps.Next())
	{
		areas = AddAreaToAreas(areas, overlaps.Item());
	}

	DrawAreas uppers = GetOverlapAreas(dsc, upperAreas);

	for (uppers.Begin(); !uppers.IsEnd(); uppers.Next())
	{
		areas = CutAreaFromAreas(areas, uppers.Item());
	}

	return areas;
}
