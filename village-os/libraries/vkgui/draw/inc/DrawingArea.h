//###########################################################################
// DrawingArea.h
// Declarations of the functions that about drawing area
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_AREA_H__
#define __DRAWING_AREA_H__

#include "DrawingBase.h"


/// @brief DrawingArea
class DrawingArea : public DrawingBase
{
public:
	//Methods
	void Set
	(
		int x,
		int y,
		int width,
		int height,
		int* area
	);

	void Get
	(
		int x,
		int y,
		int width,
		int height,
		int* area
	);
};

#endif //!__DRAWING_AREA_H__
