//###########################################################################
// Window.cpp
// Definitions of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Window.h"
#include "Display.h"


/// @brief 
Window::Window()
	:locX(0),
	locY(0),
	locZ(0),
	cursor(NULL)
{
	Wedget();
}


/// @brief 
void Window::Initialize()
{
	cursor = CreateWedget(Wedget::_Cursor);
	cursor->SetLocation(0, 0, 5, 5);
}


/// @brief 
/// @param code 
/// @param status 
void Window::UpdateKey(int code, int status)
{

}


/// @brief 
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Window::UpdateCursor(int axisX, int axisY, int axisZ)
{
	locX += axisX;
	locY -= axisY;

	if (locX < 0) locX = 0;
	else if (locX > (width - 5)) locX = (width - 5);
	if (locY < 0) locY = 0;
	else if (locY > (height - 5)) locY = (height - 5);

	cursor->SetLocation(locX, locY, 5, 5);
	cursor->Show();
}


/// @brief Initialize
void Window::Show()
{
	int locX = GetLocX();
	int locY = GetLocY();
	display->DrawRectangle(locX, locY, width - 1, height - 1);
	Wedget::Show();
}
