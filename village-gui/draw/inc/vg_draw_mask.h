//###########################################################################
// vg_draw_mask.h
// Declarations of the functions that about draw mask
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_MASK_H__
#define __VG_DRAW_MASK_H__

#include "vg_draw_defs.h"


/// @brief DrawMask
class DrawMask
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

#endif //!__VG_DRAW_MASK_H__
