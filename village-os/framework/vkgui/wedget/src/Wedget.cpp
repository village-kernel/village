//###########################################################################
// Wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Wedget.h"
#include "Wedgets.h"


/// @brief Constructor
Wedget::Wedget()
	:display(NULL),
	x(0),
	y(0),
	xoff(0),
	yoff(0),
	width(0),
	height(0),
	bg(NULL)
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief Create Wedget
/// @param id 
/// @return 
Wedget* Wedget::CreateWedget(Wedget::WedgetID id)
{
	Wedget* wedget = NULL;

	switch (id)
	{
		case _Button:
			wedget = new Button();
			break;
		case _Cursor:
			wedget = new Cursor();
			break;
		case _Frame:
			wedget = new Frame();
			break;
		case _Label:
			wedget = new Label();
			break;
		case _ListBox:
			wedget = new ListBox();
			break;
		case _Menu:
			wedget = new Menu();
			break;
		case _MsgBox:
			wedget = new MsgBox();
			break;
		case _Tabbar:
			wedget = new Tabbar();
			break;
		case _TextBox:
			wedget = new TextBox();
			break;
		case _Toolbar:
			wedget = new Toolbar();
			break;
		case _Window:
			wedget = new Window();
			break;
		default: break;
	}

	if (NULL != wedget)
	{
		wedget->SetDisplay(display);
		wedget->SetLocationOffset(x, y);
		wedget->Setup();
		wedgets.Add(wedget);
	}

	return wedget;
}


/// @brief Set display
/// @param display 
void Wedget::SetDisplay(Display* display)
{
	this->display = display;
}


/// @brief Wedget SetLocation
/// @param x : x coordinate
/// @param y : y coordinate
/// @param width : width
/// @param height : height
void Wedget::SetLocation(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


/// @brief Wedget SetLocation offset
/// @param xoff 
/// @param yoff 
void Wedget::SetLocationOffset(int xoff, int yoff)
{
	this->xoff = xoff;
	this->yoff = yoff;
}


/// @brief 
/// @return 
int Wedget::GetLocX()
{
	return x + xoff;
}


/// @brief 
/// @return 
int Wedget::GetLocY()
{
	return y + yoff;
}


/// @brief 
/// @return 
int Wedget::GetWidth()
{
	return width;
}


/// @brief 
/// @return 
int Wedget::GetHeight()
{
	return height;
}


/// @brief Wedget background
/// @param bg : background
void Wedget::SetBackground(Wedget* bg)
{
	this->bg = bg;
}


/// @brief Wedget default steup 
void Wedget::Setup()
{

}


/// @brief Wedget default show
void Wedget::Show()
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->Show();
	}
}


/// @brief Wedget default refresh
void Wedget::Refresh()
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->Refresh();
	}
}
