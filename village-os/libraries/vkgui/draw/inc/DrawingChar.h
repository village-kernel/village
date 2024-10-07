//###########################################################################
// DrawingChar.h
// Declarations of the functions that about drawing char
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_CHAR_H__
#define __DRAWING_CHAR_H__

#include "DrawingBase.h"


/// @brief DrawingChar
class DrawingChar : public DrawingBase
{
public:
	//Methods
	void Set
	(
		int x,
		int y,
		char chr,
		DrawingDefs::FontSize fontSize = DrawingDefs::Font16,
		DrawingDefs::DrawingMode mode = DrawingDefs::Multiply,
		int color = DrawingDefs::defStrokeColor
	);
};

#endif //!__DRAWING_CHAR_H__
