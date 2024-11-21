//###########################################################################
// vg_window.cpp
// Definitions of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_window.h"


/// @brief Constructor
Window::Window()
{
}


/// @brief Destructor
Window::~Window()
{
}


/// @brief Init content
void Window::InitContent()
{
	
}


/// @brief Draw content
void Window::DrawContent()
{
	rect.Execute(area, area, DrawDefs::White);

	sysinfo->draws.Put(&rect.Output);
}


/// @brief Place on top
void Window::PlaceOnTop()
{
	isTop = true;
}


/// @brief Cancel on top
void Window::CancelOnTop()
{
	isTop = false;
}


/// @brief Is on top
/// @return 
bool Window::IsOnTop()
{
	return isTop;
}
