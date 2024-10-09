//###########################################################################
// DrawingString.h
// Declarations of the functions that about drawing string
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_STRING_H__
#define __DRAWING_STRING_H__

#include "DrawingBase.h"


/// @brief DrawingString
class DrawingString : public DrawingBase
{
public:
	//Methods
	void Set
	(
		int x,
		int y,
		char* str,
		int font = DrawingDefs::Font16,
		int mode = DrawingDefs::Multiply,
		int color = DrawingDefs::defStrokeColor
	);
};

#endif //!__DRAWING_STRING_H__
