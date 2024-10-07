//###########################################################################
// DrawingCircle.h
// Declarations of the functions that about drawing circle
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_CIRCLE_H__
#define __DRAWING_CIRCLE_H__

#include "DrawingBase.h"


/// @brief DrawingCircle
class DrawingCircle : public DrawingBase
{
public:
	//Methods
	void Set(int x, int y, int r, int* colors = NULL);
	void Get(int x, int y, int r, int* colors = NULL);
};

#endif //!__DRAWING_CIRCLE_H__
