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


/// @brief Wedget Initiate
/// @param devices 
void Window::Initiate(GraphicsDevices* devices)
{
	Wedget::Initiate(devices);
}


/// @brief Wedget Execute
/// @param input 
void Window::Execute(IndevData input)
{

}
