//###########################################################################
// vg_draw_arc.h
// Declarations of the functions that about draw arc
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_ARC_H__
#define __VG_DRAW_ARC_H__

#include "vg_draw_defs.h"


/// @brief DrawArc
class DrawArc
{
public:
	//Methods
	void Execute
	(
		int x,
		int y,
		int r,
		int* colors = NULL
	);
};

#endif //!__VG_DRAW_ARC_H__
