//###########################################################################
// vg_draw_line.h
// Declarations of the functions that about draw line
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_LINE_H__
#define __VG_DRAW_LINE_H__

#include "vg_draw_defs.h"


/// @brief DrawLine
class DrawLine
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

#endif //!__VG_DRAW_LINE_H__
