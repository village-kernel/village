//###########################################################################
// DrawingBase.cpp
// Definitions of the functions that manage drawing base
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DrawingBase.h"
#include "Drawing.h"


/// @brief Setup
/// @param drawing 
/// @return 
bool DrawingBase::Setup(Drawing* drawing)
{
	this->drawing = drawing;

	if ((NULL != drawing) && (NULL != drawing->fbdev))
	{
		limitX = drawing->fbdev->info.width - 1;
		limitY = drawing->fbdev->info.height - 1;
	}

	return (NULL != drawing);
}


/// @brief Exit
void DrawingBase::Exit()
{
	limitX = 0;
	limitY = 0;
}
