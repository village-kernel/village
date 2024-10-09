//###########################################################################
// DrawingClear.h
// Declarations of the functions that about drawing clear
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_CLEAR_H__
#define __DRAWING_CLEAR_H__

#include "DrawingBase.h"


/// @brief DrawingClear
class DrawingClear : public DrawingBase
{
public:
	//Methods
	void Set(int color = DrawingDefs::defBgColor);
};

#endif //!__DRAWING_CLEAR_H__
