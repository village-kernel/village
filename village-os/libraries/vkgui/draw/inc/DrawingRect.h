//###########################################################################
// DrawingRect.h
// Declarations of the functions that about drawing rect
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_RECT_H__
#define __DRAWING_RECT_H__

#include "DrawingBase.h"


/// @brief DrawingRect
class DrawingRect : public DrawingBase
{
public:
	//Methods
	void Set
	(
		int x0,
		int y0,
		int x1,
		int y1,
		int color = DrawingDefs::defStrokeColor
	);
};

#endif //!__DRAWING_RECT_H__
