//###########################################################################
// Scrollbar.cpp
// Definitions of the functions that manage scroll bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scrollbar.h"


/// @brief Constructor
Scrollbar::Scrollbar()
	:dir(_Vertical),
	scrollbtn(NULL)
{
}


/// @brief Destructor
Scrollbar::~Scrollbar()
{
}


/// @brief Init content
void Scrollbar::InitContent()
{
	//scrollbtn = new Button();
	//scrollbtn->SetSize(40, 0, 20, 20);
	//AddWedget(scrollbtn);
}


/// @brief Draw content
void Scrollbar::DrawContent()
{

}


/// @brief 
/// @param dir 
void Scrollbar::SetDirection(Direction dir)
{
	this->dir = dir;
}
