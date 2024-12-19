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
	place(_Middle),
	resizeSide(0)
{
}


/// @brief Destructor
Window::~Window()
{
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
	resizeSide = 0;

	if ((math.IsInRange(x, layerArea.sx - resize_range, layerArea.ex + resize_range)) &&
		(math.IsInRange(y, layerArea.sy - resize_range, layerArea.ey + resize_range)))
	{
		if (math.IsInRange(x - layerArea.sx, -resize_range, resize_range))
			resizeSide |= ResizeSide::_LeftSide;
		if (math.IsInRange(layerArea.ex - x, -resize_range, resize_range))
			resizeSide |= ResizeSide::_RightSide;
		if (math.IsInRange(y - layerArea.sy, -resize_range, resize_range))
			resizeSide |= ResizeSide::_UpSide;
		if (math.IsInRange(layerArea.ey - y, -resize_range, resize_range))
			resizeSide |= ResizeSide::_DownSide;
	}

	return (0 != resizeSide);
}


/// @brief Wedget set size
/// @param width 
/// @param height 
void Window::SetSize(int width, int height)
{
	Wedget::SetSize(width, height);

	navbar.SetSize(GetWidth(), navbar_height);
}


/// @brief Wedget resize size
/// @param axisx 
/// @param axisy 
void Window::Resize(int axisx, int axisy)
{
	if (resizeSide & ResizeSide::_LeftSide)
		layerArea.sx += axisx;
	if (resizeSide & ResizeSide::_RightSide)
		layerArea.ex += axisx;
	if (resizeSide & ResizeSide::_UpSide)
		layerArea.sy += axisy;
	if (resizeSide & ResizeSide::_DownSide)
		layerArea.ey += axisy;
	
	navbar.SetSize(GetWidth(), navbar_height);
	navbar.MoveTo(GetX(), GetY());
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
