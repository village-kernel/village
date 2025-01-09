//###########################################################################
// vg_scrollbar.cpp
// Definitions of the functions that manage scroll bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_scrollbar.h"


/// @brief Constructor
VgScrollbar::VgScrollbar()
	:dir(_Vertical),
	scrollbtn(NULL)
{
	SetTitle((char*)"scrollbar");
}


/// @brief Destructor
VgScrollbar::~VgScrollbar()
{
}


/// @brief 
/// @param dir 
void VgScrollbar::SetDirection(Direction dir)
{
	this->dir = dir;
}


/// @brief VgScrollbar initiate
/// @param devices 
void VgScrollbar::InitContent(VgDevices* devices)
{

}


/// @brief VgScrollbar execute
/// @param input 
void VgScrollbar::ExecContent(VgInputData input)
{

}


/// @brief VgScrollbar draw
/// @param drawArea 
void VgScrollbar::DrawContent(VgDrawArea drawArea)
{

}
