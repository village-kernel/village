//###########################################################################
// vg_draw_image.h
// Declarations of the functions that about draw image
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DRAW_IMAGE_H__
#define __VG_DRAW_IMAGE_H__

#include "vg_draw_defs.h"


/// @brief DrawImage
class DrawImage
{
public:
	//Methods
	void Execute
	(
		int x,
		int y,
		char chr,
		int font = DrawDefs::Font16,
		int mode = DrawDefs::Multiply,
		int color = DrawDefs::defStrokeColor
	);
};

#endif //!__VG_DRAW_IMAGE_H__
