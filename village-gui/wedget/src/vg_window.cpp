//###########################################################################
// vg_window.cpp
// Definitions of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_window.h"


/// @brief Constructor
Window::Window()
	:focus(false),
	place(_Middle)
{
}


/// @brief Destructor
Window::~Window()
{
}


/// @brief 
/// @param width 
/// @param height 
void Window::SetSize(int width, int height)
{
	Wedget::SetSize(width, height);

	navbar.SetSize(GetWidth(), navbar_height);
}


/// @brief Wedget resize size
/// @param x 
/// @param y 
/// @param axisx 
/// @param axisy 
void Window::Resize(int x, int y, int axisx, int axisy)
{

}


/// @brief Set enable navbar
/// @param enable 
void Window::SetEnableNavbar(bool enable)
{
	navbar.SetEnable(enable);
}


/// @brief Is enable navbar
/// @return 
bool Window::IsEnableNavbar()
{
	return navbar.IsEnable();
}


/// @brief Set hidden navbar
/// @param hidden 
void Window::SetHiddenNavbar(bool hidden)
{
	navbar.SetHidden(hidden);
}


/// @brief Is hidden navbar
/// @return 
bool Window::IsHiddenNavbar()
{
	return navbar.IsHidden();
}


/// @brief Set always focus
/// @param focus 
void Window::SetAlwaysFocus(bool focus)
{
	this->focus = focus;
}


/// @brief Is always focus
/// @return 
bool Window::IsAlwaysFocus()
{
	return focus;
}


/// @brief Wedget set place
/// @param place 
void Window::SetPlace(Place place)
{
	this->place = place;
}


/// @brief Wedget get place
/// @return 
Window::Place Window::GetPlace()
{
	return place;
}


/// @brief Is in move area
/// @param x 
/// @param y 
/// @return 
bool Window::IsInMoveArea(int x, int y)
{
	bool res = false;

	if (!navbar.IsHidden() && navbar.IsEnable())
		res = navbar.IsInMoveArea(x, y);
	else
		res = layer.IsCoordinateInArea(x, y, layerArea);

	return res;
}


/// @brief Is in resize area
/// @param x 
/// @param y 
/// @return 
bool Window::IsInResizeArea(int x, int y)
{
	return false;
}


/// @brief Wedget Initiate
/// @param devices 
void Window::Initiate(VgDevices* devices)
{
	Wedget::Initiate(devices);

	AddWedget(&navbar);
}


/// @brief Wedget Execute
/// @param input 
void Window::Execute(IndevData input)
{
	Wedget::Execute(input);
}
