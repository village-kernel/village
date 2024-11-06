//###########################################################################
// vg_draw_triangle.h
// Declarations of the functions that about draw triangle
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_TRIANGLE_H__
#define __VG_DRAW_TRIANGLE_H__

#include "vg_draw_defs.h"


/// @brief DrawTriangle
class DrawTriangle
{
public:
	//Methods
	void Execute
	(
		int x,
		int y,
		int width,
		int height,
		int* area
	);
};

#endif //!__VG_DRAW_TRIANGLE_H__
