//###########################################################################
// vg_navbar.cpp
// Definitions of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_navbar.h"


/// @brief Constructor
VgNavbar::VgNavbar()
{
	SetTitle((char*)"navbar");
}


/// @brief Destructor
VgNavbar::~VgNavbar()
{
}


/// @brief Get exit button
/// @return 
VgButton* VgNavbar::GetExitBtn()
{
	return &exitbtn;
}


/// @brief Get min button
/// @return 
VgButton* VgNavbar::GetMinBtn()
{
	return &minbtn;
}


/// @brief Get max button
/// @return 
VgButton* VgNavbar::GetMaxBtn()
{
	return &maxbtn;
}


/// @brief Is in maximize area
/// @param x 
/// @param y 
/// @return 
bool VgNavbar::IsInMaximizeArea(int x, int y)
{
	return maxbtn.IsInLayerArea(x, y);
}


/// @brief Is in minimize area
/// @param x 
/// @param y 
/// @return 
bool VgNavbar::IsInMinimizeArea(int x, int y)
{
	return minbtn.IsInLayerArea(x, y);
}


/// @brief Is in close area
/// @param x 
/// @param y 
/// @return 
bool VgNavbar::IsInCloseArea(int x, int y)
{
	return exitbtn.IsInLayerArea(x, y);
}


/// @brief VgNavbar initiate
/// @param devices 
void VgNavbar::InitContent(VgDevices* devices)
{
	exitbtn.AxisMove(exit_btn_x, btn_y);
	exitbtn.SetSize(btn_width, btn_height);
	exitbtn.SetText((char*)"X");
	exitbtn.SetBgColor(VgDrawDefs::_Red);
	AddWedget(&exitbtn);

	minbtn.AxisMove(min_btn_x, btn_y);
	minbtn.SetSize(btn_width, btn_height);
	minbtn.SetText((char*)"-");
	minbtn.SetBgColor(VgDrawDefs::_Yellow);
	AddWedget(&minbtn);

	maxbtn.AxisMove(max_btn_x, btn_y);
	maxbtn.SetSize(btn_width, btn_height);
	maxbtn.SetText((char*)"O");
	maxbtn.SetBgColor(VgDrawDefs::_Green);
	AddWedget(&maxbtn);
}


/// @brief VgNavbar execute
/// @param input 
void VgNavbar::ExecContent(VgInputData input)
{

}


/// @brief VgNavbar draw
/// @param drawArea 
void VgNavbar::DrawContent(VgDrawArea drawArea)
{

}
