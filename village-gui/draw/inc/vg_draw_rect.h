//###########################################################################
// vg_draw_rect.h
// Declarations of the functions that about draw rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_RECT_H__
#define __VG_DRAW_RECT_H__

#include "vg_draw_defs.h"


/// @brief DrawRect
class DrawRect
{
public:
	//Methods
	void Execute
	(
		int x0,
		int y0,
		int x1,
		int y1,
		int color = DrawDefs::defStrokeColor
	);
};

#endif //!__VG_DRAW_RECT_H__
