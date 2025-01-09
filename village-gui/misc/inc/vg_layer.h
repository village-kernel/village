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

/// @brief VgLayer
class VgLayer
{
private:
	//Members
	VgMath math;
public:
	//Methods
	VgLayer();
	~VgLayer();
	bool IsCoordinateInArea(int x, int y, VgDrawArea area);
	bool IsAreaOverlap(VgDrawArea a0, VgDrawArea a1);
	bool IsAreaSame(VgDrawArea a0, VgDrawArea a1);
	bool IsAreaVaild(VgDrawArea dsc);
	VgDrawArea GetOverlapArea(VgDrawArea a0, VgDrawArea a1);
	VgDrawAreas GetOverlapAreas(VgDrawArea dsc, VgDrawAreas areas);
	VgDrawAreas CutOverlapAreas(VgDrawArea a0, VgDrawArea a1);
public:
	//Methods
	VgDrawAreas AddAreaToAreas(VgDrawAreas dscs, VgDrawArea area);
	VgDrawAreas AddAreasToAreas(VgDrawAreas dscs, VgDrawAreas areas);
	VgDrawAreas CutAreaFromAreas(VgDrawAreas dscs, VgDrawArea area);
	VgDrawAreas CutAreasFromAreas(VgDrawAreas dscs, VgDrawAreas areas);
	VgDrawAreas CalcOverlapAreas(VgDrawArea dsc, VgDrawAreas overlapAreas, VgDrawAreas upperAreas);
};

#endif //!__VG_LAYER_H__
