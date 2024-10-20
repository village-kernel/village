//###########################################################################
// DrawingClear.cpp
// Definitions of the functions that manage drawing clear
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingClear.h"
#include "Drawing.h"



/// @brief Drawing clear set
/// @param color 
void DrawingClear::Set(int color)
{
	if (NULL != drawing->fbdev)
	{
		drawing->fbdev->Clear(color);
	}
}
