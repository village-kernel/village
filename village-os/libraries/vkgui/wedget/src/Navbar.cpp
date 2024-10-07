//###########################################################################
// Navbar.cpp
// Definitions of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Navbar.h"


/// @brief 
Navbar::Navbar()
	:minbtn(NULL),
	maxbtn(NULL),
	exitbtn(NULL)
{
}


/// @brief 
/// @param drawing 
/// @param x 
/// @param y 
void Navbar::InitContent()
{
	minbtn = (Button*)CreateWedget(WedgetID::_Button);
	minbtn->Resize(40, 0, 20, 20);
	minbtn->SetText((char*)"-");

	maxbtn = (Button*)CreateWedget(WedgetID::_Button);
	maxbtn->Resize(20, 0, 20, 20);
	maxbtn->SetText((char*)"O");

	exitbtn = (Button*)CreateWedget(WedgetID::_Button);
	exitbtn->Resize(0, 0, 20, 20);
	exitbtn->SetText((char*)"X");
}
