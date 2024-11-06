//###########################################################################
// vg_draw_label.h
// Declarations of the functions that about draw label
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_LABEL_H__
#define __VG_DRAW_LABEL_H__

#include "vg_draw_defs.h"


/// @brief DrawLabel
class DrawLabel
{
public:
	//Methods
	void Execute
	(
		int x,
		int y,
		char* str,
		int font = DrawDefs::Font16,
		int mode = DrawDefs::Multiply,
		int color = DrawDefs::defStrokeColor
	);
};

#endif //!__VG_DRAW_LABEL_H__
