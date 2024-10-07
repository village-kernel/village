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
		int* area,
		int x = 0,
		int y = 0,
		int width = 0,
		int height = 0
	);
};

#endif //!__DRAWING_AREA_H__
