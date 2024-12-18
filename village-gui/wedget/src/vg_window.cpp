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


/// @brief Wedget resize size
/// @param x 
/// @param y 
/// @param axisx 
/// @param axisy 
void Window::Resize(int x, int y, int axisx, int axisy)
{

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
	return layer.IsCoordinateInArea(x, y, layerArea);
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
}


/// @brief Wedget Execute
/// @param input 
void Window::Execute(IndevData input)
{
	Wedget::Execute(input);
}
