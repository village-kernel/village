//###########################################################################
// vg_layer.h
// Declarations of the functions that manage layer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LAYER_H__
#define __VG_LAYER_H__

#include "vg_draw_defs.h"
#include "vg_math.h"
#include "vg_list.h"

/// @brief Layer
class Layer
{
private:
	//Members
	Math math;
public:
	//Methods
	Layer();
	~Layer();
	bool IsCoordinateInArea(int x, int y, DrawArea area);
	bool IsAreaOverlap(DrawArea a0, DrawArea a1);
	bool IsAreaSame(DrawArea a0, DrawArea a1);
	bool IsAreaVaild(DrawArea dsc);
	DrawArea GetOverlapArea(DrawArea a0, DrawArea a1);
	DrawAreas GetOverlapAreas(DrawArea dsc, DrawAreas areas);
	DrawAreas CutOverlapAreas(DrawArea a0, DrawArea a1);
public:
	//Methods
	DrawAreas AddAreaToAreas(DrawAreas dscs, DrawArea area);
	DrawAreas AddAreasToAreas(DrawAreas dscs, DrawAreas areas);
	DrawAreas CutAreaFromAreas(DrawAreas dscs, DrawArea area);
	DrawAreas CutAreasFromAreas(DrawAreas dscs, DrawAreas areas);
	DrawAreas CalcOverlapAreas(DrawArea dsc, DrawAreas overlapAreas, DrawAreas upperAreas);
};

#endif //!__VG_LAYER_H__
