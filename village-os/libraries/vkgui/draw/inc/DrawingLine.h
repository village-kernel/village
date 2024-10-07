//###########################################################################
// DrawingLine.h
// Declarations of the functions that about drawing line
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_LINE_H__
#define __DRAWING_LINE_H__

#include "DrawingBase.h"


/// @brief DrawingLine
class DrawingLine : public DrawingBase
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

#endif //!__DRAWING_LINE_H__
