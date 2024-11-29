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
#include "vk_list.h"


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
	DrawArea GetOverlapArea(DrawArea a0, DrawArea a1);
	DrawArea CutOverlapArea(DrawArea a0, DrawArea a1);
	List<DrawArea> InciseOverlapArea(DrawArea a0, DrawArea a1);
	List<DrawArea> MovedOverlapArea(DrawArea oldArea, DrawArea newArea);
};

#endif //!__VG_LAYER_H__
