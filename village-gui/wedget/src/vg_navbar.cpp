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


/// @brief Is in maximize area
/// @param x 
/// @param y 
/// @return 
bool Navbar::IsInMaximizeArea(int x, int y)
{
	return maxbtn.IsInArea(x, y);
}


/// @brief Is in minimize area
/// @param x 
/// @param y 
/// @return 
bool Navbar::IsInMinimizeArea(int x, int y)
{
	return minbtn.IsInArea(x, y);
}


/// @brief Is in close area
/// @param x 
/// @param y 
/// @return 
bool Navbar::IsInCloseArea(int x, int y)
{
	return exitbtn.IsInArea(x, y);
}


/// @brief Wedget Initiate
/// @param devices 
void Navbar::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	exitbtn.AxisMove(exit_btn_x, btn_y);
	exitbtn.SetSize(btn_width, btn_height);
	exitbtn.SetText((char*)"X");
	exitbtn.SetBgColor(DrawDefs::_Red);
	AddWedget(&exitbtn);

	minbtn.AxisMove(min_btn_x, btn_y);
	minbtn.SetSize(btn_width, btn_height);
	minbtn.SetText((char*)"-");
	minbtn.SetBgColor(DrawDefs::_Yellow);
	AddWedget(&minbtn);

	maxbtn.AxisMove(max_btn_x, btn_y);
	maxbtn.SetSize(btn_width, btn_height);
	maxbtn.SetText((char*)"O");
	maxbtn.SetBgColor(DrawDefs::_Green);
	AddWedget(&maxbtn);
}
