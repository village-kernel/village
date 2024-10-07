//###########################################################################
// Drawing.cpp
// Definitions of the functions that manage drawing
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Drawing.h"
#include "stdarg.h"
#include "stdio.h"


/// @brief Constructor
Drawing::Drawing()
	:limitX(0),
	limitY(0)
{
}


/// @brief Destrucotr
Drawing::~Drawing()
{
}


/// @brief Display Setup
void Drawing::Setup(FBDriver* fbdev)
{
	if (NULL != fbdev)
	{
		this->fbdev = fbdev;
		limitX = fbdev->info.width - 1;
		limitY = fbdev->info.height - 1;
	}
	Clear();
}


/// @brief Display Exit
void Drawing::Exit()
{
	Clear();
}


/// @brief Display clear
/// @param color 
void Drawing::Clear(int color)
{
	if (NULL != fbdev)
	{
		fbdev->Clear(color);
	}
}
