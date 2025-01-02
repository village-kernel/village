//###########################################################################
// vg_scrollbar.cpp
// Definitions of the functions that manage scroll bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_scrollbar.h"


/// @brief Constructor
Scrollbar::Scrollbar()
	:dir(_Vertical),
	scrollbtn(NULL)
{
	SetTitle((char*)"scrollbar");
}


/// @brief Destructor
Scrollbar::~Scrollbar()
{
}


/// @brief 
/// @param dir 
void Scrollbar::SetDirection(Direction dir)
{
	this->dir = dir;
}
