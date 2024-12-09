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

	//Methods
	bool SiftOverlapArea(DrawArea dsc, VgList<DrawArea> areas);
	DrawArea CutOverlapArea(DrawArea dsc, VgList<DrawArea> areas);
	VgList<DrawArea> InciseOverlapArea(DrawArea area, VgList<DrawArea> areas);
public:
	//Methods
	Layer();
	~Layer();
	bool IsCoordinateInArea(int x, int y, DrawArea area);
	bool IsAreaOverlap(DrawArea a0, DrawArea a1);
	bool IsAreaSame(DrawArea a0, DrawArea a1);
	bool IsAreaCovered(DrawArea a0, DrawArea a1);
	bool IsAreaVaild(DrawArea dsc);
	
	DrawArea GetOverlapArea(DrawArea a0, DrawArea a1);
	DrawArea CutCoveredArea(DrawArea a0, DrawArea a1);
	DrawArea CutOverlapArea(DrawArea a0, DrawArea a1);
	VgList<DrawArea> InciseOverlapArea(DrawArea a0, DrawArea a1);
	VgList<DrawArea> MovedOverlapArea(DrawArea oldArea, DrawArea newArea);

	VgList<DrawArea> GetOverlapAreas(DrawArea dsc, VgList<DrawArea> areas);
	VgList<DrawArea> SiftOverlapAreas(VgList<DrawArea> areas);
	VgList<DrawArea> CutOverlapAreas(VgList<DrawArea> areas);
	VgList<DrawArea> InciseOverlapAreas(VgList<DrawArea> areas);
};

#endif //!__VG_LAYER_H__
