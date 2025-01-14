//###########################################################################
// vg_cursor.cpp
// Definitions of the functions that manage cursor
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_cursor.h"


/// @brief Constructor
VgCursor::VgCursor()
{
	SetTitle((char*)"cursor");
}


/// @brief Destructor
VgCursor::~VgCursor()
{
}


/// @brief VgCursor initiate
/// @param devices 
void VgCursor::InitContent(VgDevices* devices)
{
	AxisMove(-4, -4);
	SetSize(8, 8);
	SetPlace(VgCursor::_Top);
	SetBgColor(VgDrawDefs::_Black);
	SetHiddenNavbar(true);
}


/// @brief VgCursor execute
/// @param input 
void VgCursor::ExecContent(VgInputData input)
{
	VgUpdateAreas areas;

	resizeMethod = VgWindow::_Move;
	areas.oldAreas = GetResizeAreas(input);
	areas.newAreas.Add(GetLayerArea());

	this->resizeAreas = areas;
}


/// @brief VgCursor draw
/// @param drawArea 
void VgCursor::DrawContent(VgDrawArea drawArea)
{

}
