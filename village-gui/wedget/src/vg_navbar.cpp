//###########################################################################
// vg_navbar.cpp
// Definitions of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_navbar.h"


/// @brief Constructor
Navbar::Navbar()
{
}


/// @brief Destructor
Navbar::~Navbar()
{
}


/// @brief Wedget Initiate
/// @param devices 
void Navbar::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	exitbtn.Move(0, 0);
	exitbtn.SetSize(20, 20);
	exitbtn.SetText((char*)"X");
	exitbtn.SetBgColor(DrawDefs::_Red);
	AddWedget(&exitbtn);

	minbtn.Move(20, 0);
	minbtn.SetSize(20, 20);
	minbtn.SetText((char*)"-");
	minbtn.SetBgColor(DrawDefs::_Yellow);
	AddWedget(&minbtn);

	maxbtn.Move(40, 0);
	maxbtn.SetSize(20, 20);
	maxbtn.SetText((char*)"O");
	maxbtn.SetBgColor(DrawDefs::_Green);
	AddWedget(&maxbtn);
}
