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


/// @brief Layer is area covered
/// @param a0 
/// @param a1 
/// @return 
bool Layer::IsAreaCovered(DrawArea a0, DrawArea a1)
{
	return (a0.sx >= a1.sx && a0.ex <= a1.sx && 
			a0.sy >= a1.sy && a0.ey <= a1.sy);
}


/// @brief 
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


/// @brief Layer cut the overlap area
/// @param a0 
/// @param a1 
/// @return 
DrawArea Layer::CutCoveredArea(DrawArea a0, DrawArea a1)
{
	DrawArea a = a0;

	if (a0.sy >= a1.sy && a0.ey <= a1.ey)
	{
		if (a0.sx >= a1.sx && a0.sx <= a1.ex)
			a.sx = a1.ex;
		if (a0.ex >= a1.sx && a0.ex <= a1.ex)
			a.ex = a1.sx;
	}

	if (a0.sx >= a1.sx && a0.ex <= a1.ex)
	{
		if (a0.sy >= a1.sy && a0.sy <= a1.ey)
			a.sy = a1.ey;
		if (a0.ey >= a1.sy && a0.ey <= a1.ey)
			a.ey = a1.sy;
	}

	return a;
}


/// @brief Layer cut the overlap area
/// @param a0 
/// @param a1 
/// @return 
DrawArea Layer::CutOverlapArea(DrawArea a0, DrawArea a1)
{
	DrawArea a = a0;

	if (a0.sy >= a1.sy && a0.ey <= a1.ey)
	{
		if (a0.sx > a1.sx && a0.sx < a1.ex && a0.ex > a1.ex)
			a.sx = a1.ex;
		if (a0.ex > a1.sx && a0.ex < a1.ex && a0.sx < a1.sx)
			a.ex = a1.sx;
	}

	if (a0.sx >= a1.sx && a0.ex <= a1.ex)
	{
		if (a0.sy >= a1.sy && a0.sy < a1.ey && a0.ey > a1.ey)
			a.sy = a1.ey;
		if (a0.ey > a1.sy && a0.ey <= a1.ey && a0.sy < a1.sy)
			a.ey = a1.sy;
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
	if (a0.sy < a1.sy)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a0.sy;
		a.ey = a1.sy;
		list.Add(a);
	}

	//Under
	if (a0.ey > a1.ey)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a0.ex;
		a.sy = a1.ey;
		a.ey = a0.ey;
		list.Add(a);
	}

	//Left
	if (a0.sx < a1.sx)
	{
		DrawArea a;
		a.sx = a0.sx;
		a.ex = a1.sx;
		a.sy = math.Max(a0.sy, a1.sy);
		a.ey = math.Min(a0.ey, a1.ey);
		list.Add(a);
	}

	//Right
	if (a0.ex > a1.ex)
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


/// @brief Get overlap areas
/// @return 
List<DrawArea> Layer::GetOverlapAreas(DrawArea dsc, List<DrawArea> areas)
{
	List<DrawArea> getAreas;

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


/// @brief 
/// @param dsc 
/// @param areas 
/// @return 
bool Layer::SiftOverlapArea(DrawArea dsc, List<DrawArea> areas)
{
	DrawArea tmp = dsc;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		if (IsAreaSame(dsc, area)) continue;

		tmp = CutCoveredArea(tmp, area);
		
		if (!IsAreaVaild(tmp)) return false;
	}
	return true;
}


/// @brief 
/// @param areas 
/// @return 
List<DrawArea> Layer::SiftOverlapAreas(List<DrawArea> areas)
{
	List<DrawArea> siftAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		if (SiftOverlapArea(area, areas))
		{
			siftAreas.Add(area);
		}
	}

	return siftAreas;
}


/// @brief Cut overlap area
/// @param area 
/// @param areas 
/// @return 
DrawArea Layer::CutOverlapArea(DrawArea dsc, List<DrawArea> areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		if (IsAreaSame(dsc, area)) continue;

		if (!IsAreaOverlap(dsc, area)) continue;
		
		dsc = CutOverlapArea(dsc, area);
	}

	return dsc;
}


/// @brief Cut overlap areas
/// @param areas 
/// @return 
List<DrawArea> Layer::CutOverlapAreas(List<DrawArea> areas)
{
	List<DrawArea> cutAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		area = CutOverlapArea(area, areas);

		cutAreas.Add(area);
	}

	return cutAreas;
}


/// @brief 
/// @param area 
/// @param areas 
/// @return 
List<DrawArea> Layer::InciseOverlapArea(DrawArea area, List<DrawArea> areas)
{
	List<DrawArea> inciseAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea temp = areas.Item();

		if (IsAreaSame(area, temp)) continue;

		if (!IsAreaOverlap(area, temp)) continue;
		
		List<DrawArea> list = InciseOverlapArea(area, temp);

		if (0 != list.GetSize())
		{
			inciseAreas.Append(list);
		}
		else inciseAreas.Add(area);
	}

	return inciseAreas;
}


/// @brief Incise actived wedget overlap areas
/// @param areas 
/// @return 
List<DrawArea> Layer::InciseOverlapAreas(List<DrawArea> areas)
{
	List<DrawArea> inciseAreas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		inciseAreas.Append(InciseOverlapArea(area, areas));
	}
	
	return inciseAreas;
}
