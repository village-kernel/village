//###########################################################################
// DrawingBase.h
// Declarations of the functions that about drawing base
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_BASE_H__
#define __DRAWING_BASE_H__

#include "DrawingDefs.h"


/// @brief Drawing
class Drawing;


/// @brief DrawingBase
class DrawingBase
{
protected:
	//Members
	Drawing* drawing;
	int      limitX;
	int      limitY;
public:
	//Methods
	virtual bool Setup(Drawing* drawing);
	virtual void Exit();
};

#endif //!__DRAWING_BASE_H__
