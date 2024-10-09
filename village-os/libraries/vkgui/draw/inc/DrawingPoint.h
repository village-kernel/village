//###########################################################################
// DrawingPoint.h
// Declarations of the functions that about drawing point
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_POINT_H__
#define __DRAWING_POINT_H__

#include "DrawingBase.h"


/// @brief DrawingPoint
class DrawingPoint : public DrawingBase
{
public:
	//Methods
	void Set
	(
		int x,
		int y,
		int color = DrawingDefs::defStrokeColor
	);

	int Get
	(
		int x,
		int y
	);
};

#endif //!__DRAWING_POINT_H__
