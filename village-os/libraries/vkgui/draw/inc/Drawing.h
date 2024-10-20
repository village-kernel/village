//###########################################################################
// Drawing.h
// Declarations of the functions that about display algorithm
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DRAWING_H__
#define __DRAWING_H__

#include "Driver.h"
#include "DrawingPoint.h"
#include "DrawingLine.h"
#include "DrawingRect.h"
#include "DrawingCircle.h"
#include "DrawingArea.h"
#include "DrawingClear.h"
#include "DrawingChar.h"
#include "DrawingString.h"


/// @brief Drawing
class Drawing
{
public:
	//Members
	FBDriver*      fbdev;
	DrawingPoint   point;
	DrawingLine    line;
	DrawingRect    rect;
	DrawingCircle  circle;
	DrawingArea    area;
	DrawingClear   clear;
	DrawingChar    chr;
	DrawingString  string;
public:
	//Methods
	Drawing();
	~Drawing();
	void Setup(FBDriver* fbdev);
	void Exit();
};

#endif //!__DRAWING_H__
