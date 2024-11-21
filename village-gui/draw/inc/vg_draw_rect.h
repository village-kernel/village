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
	//Members
	DrawData Output;

	//Methods
	void Execute
	(
		DrawArea layerArea,
		DrawArea drawArea,
		int color
	);
};

#endif //!__VG_DRAW_RECT_H__
