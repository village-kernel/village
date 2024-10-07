//###########################################################################
// Drawing.h
// Declarations of the functions that about display algorithm
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_H__
#define __DRAWING_H__

#include "Driver.h"
#include "DrawingArea.h"
#include "DrawingChar.h"
#include "DrawingCircle.h"
#include "DrawingClear.h"
#include "DrawingLine.h"
#include "DrawingPoint.h"
#include "DrawingRect.h"
#include "DrawingString.h"


/// @brief Drawing
class Drawing
{
public:
	//Members
	FBDriver*      fbdev;
	DrawingArea    area;
	DrawingChar    chr;
	DrawingCircle  circle;
	DrawingClear   clear;
	DrawingLine    line;
	DrawingPoint   point;
	DrawingRect    rect;
	DrawingString  string;

	//Methods
	Drawing();
	~Drawing();
	void Setup(FBDriver* fbdev);
	void Exit();
};

#endif //!__DRAWING_H__
