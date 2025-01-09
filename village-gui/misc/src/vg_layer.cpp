//###########################################################################
// vg_layer.cpp
// Definitions of the functions that manage layer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_layer.h"


/// @brief Constructor
VgLayer::VgLayer()
{
}


/// @brief Destructor
VgLayer::~VgLayer()
{
}


/// @brief Layer is coordinate in the area
/// @param x 
/// @param y 
/// @param area 
/// @return 
bool VgLayer::IsCoordinateInArea(int x, int y, VgDrawArea area)
{
	return ((x >= area.sx && x <= area.ex) && 
			(y >= area.sy && y <= area.ey));
}


/// @brief Layer is area overlap
/// @param a0 
/// @param a1 
/// @return 
bool VgLayer::IsAreaOverlap(VgDrawArea a0, VgDrawArea a1)
{
	return ((math.Min(a0.ex, a1.ex) - math.Max(a0.sx, a1.sx) >= 0) &&
			(math.Min(a0.ey, a1.ey) - math.Max(a0.sy, a1.sy) >= 0));
}


/// @brief Layer is area the same
/// @param a0 
/// @param a1 
/// @return 
bool VgLayer::IsAreaSame(VgDrawArea a0, VgDrawArea a1)
{
	return (a0.sx == a1.sx && a0.ex == a1.ex && 
			a0.sy == a1.sy && a0.ey == a1.ey);
}


/// @brief Layer is area valid
/// @param dsc 
/// @return 
bool VgLayer::IsAreaVaild(VgDrawArea dsc)
{
	return ((dsc.ex - dsc.sx) > 0 && (dsc.ey - dsc.sy) > 0);
}


/// @brief Layer get the overlap area
/// @param a0 
/// @param a1 
/// @return 
VgDrawArea VgLayer::GetOverlapArea(VgDrawArea a0, VgDrawArea a1)
{
	VgDrawArea a;

	a.sx = math.Max(a0.sx, a1.sx); 
	a.ex = math.Min(a0.ex, a1.ex);
	a.sy = math.Max(a0.sy, a1.sy);
	a.ey = math.Min(a0.ey, a1.ey);

	return a;
}


/// @brief Get overlap areas
/// @return 
VgDrawAreas VgLayer::GetOverlapAreas(VgDrawArea dsc, VgDrawAreas areas)
{
	VgDrawAreas getAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		VgDrawArea area = areas.Item();

		if (IsAreaOverlap(dsc, area))
		{
			getAreas.Add(GetOverlapArea(dsc, area));
		}
	}

	return getAreas;
}


/// @brief Cut the overlap areas
/// @param a0 
/// @param a1 
/// @return 
VgDrawAreas VgLayer::CutOverlapAreas(VgDrawArea a0, VgDrawArea a1)
{
	VgDrawAreas list;

	//Not overlap
	if (!IsAreaOverlap(a0, a1))
	{
		list.Add(a0);
		return list;
	}

	//A1 enlarge by one pixel
	a1.sx = a1.sx - 1;
	a1.ex = a1.ex + 1;
	a1.sy = a1.sy - 1;
	a1.ey = a1.ey + 1;
	
	//Up
	if (a0.sy <= a1.sy)
	{
		VgDrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a0.sy;
		a.ey = a1.sy;
		list.Add(a);
	}

	//Left
	if (a0.sx <= a1.sx)
	{
		VgDrawArea a;
		a.sx = a0.sx;
		a.ex = a1.sx;
		a.sy = math.Max(a0.sy, a1.sy);
		a.ey = math.Min(a0.ey, a1.ey);
		list.Add(a);
	}

	//Right
	if (a0.ex >= a1.ex)
	{
		VgDrawArea a;
		a.sx = a1.ex;
		a.ex = a0.ex;
		a.sy = math.Max(a0.sy, a1.sy);
		a.ey = math.Min(a0.ey, a1.ey);
		list.Add(a);
	}

	//Down
	if (a0.ey >= a1.ey)
	{
		VgDrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a1.ey;
		a.ey = a0.ey;
		list.Add(a);
	}

	return list;
}


/// @brief Add area to dscs
/// @param dscs 
/// @param area 
/// @return 
VgDrawAreas VgLayer::AddAreaToAreas(VgDrawAreas dscs, VgDrawArea area)
{
	VgDrawAreas appendAreas;

	appendAreas.Add(area);

	for (dscs.Begin(); !dscs.IsEnd(); dscs.Next())
	{
		appendAreas = CutAreaFromAreas(appendAreas, dscs.Item());
	}

	dscs.Append(appendAreas);

	return dscs;
}


/// @brief Add areas to dscs
/// @param dscs 
/// @param areas 
/// @return 
VgDrawAreas VgLayer::AddAreasToAreas(VgDrawAreas dscs, VgDrawAreas areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		dscs = AddAreaToAreas(dscs, areas.Item());
	}
	return dscs;
}


/// @brief Cut area from dscs
/// @param dscs 
/// @param area 
/// @return 
VgDrawAreas VgLayer::CutAreaFromAreas(VgDrawAreas dscs, VgDrawArea area)
{
	VgDrawAreas cutAreas;

	for (dscs.Begin(); !dscs.IsEnd(); dscs.Next())
	{
		cutAreas.Append(CutOverlapAreas(dscs.Item(), area));
	}

	return cutAreas;
}


/// @brief Cut areas from dscs
/// @param dscs 
/// @param areas 
/// @return 
VgDrawAreas VgLayer::CutAreasFromAreas(VgDrawAreas dscs, VgDrawAreas areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		dscs = CutAreaFromAreas(dscs, areas.Item());
	}
	return dscs;
}


/// @brief Calc overlap areas
/// @param dsc 
/// @param overlap 
/// @param upper 
/// @return 
VgDrawAreas VgLayer::CalcOverlapAreas(VgDrawArea dsc, VgDrawAreas overlapAreas, VgDrawAreas upperAreas)
{
	VgDrawAreas areas;

	VgDrawAreas overlaps = GetOverlapAreas(dsc, overlapAreas);
	
	for (overlaps.Begin(); !overlaps.IsEnd(); overlaps.Next())
	{
		areas = AddAreaToAreas(areas, overlaps.Item());
	}

	VgDrawAreas uppers = GetOverlapAreas(dsc, upperAreas);

	for (uppers.Begin(); !uppers.IsEnd(); uppers.Next())
	{
		areas = CutAreaFromAreas(areas, uppers.Item());
	}

	return areas;
}
