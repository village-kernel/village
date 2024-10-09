//###########################################################################
// Wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Wedget.h"


/// @brief Constructor
Wedget::Wedget()
	:x(0),
	y(0),
	xoff(0),
	yoff(0),
	width(0),
	height(0),
	isChange(false),
	indev(NULL),
	drawing(NULL)
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief 
/// @return 
int Wedget::GetLocX() { return x + xoff; }


/// @brief 
/// @return 
int Wedget::GetLocY() { return y + yoff; }


/// @brief 
/// @return 
int Wedget::GetWidth() { return width; }


/// @brief 
/// @return 
int Wedget::GetHeight() { return height; }


/// @brief Wedget Setup
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void Wedget::SetSize(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


/// @brief Wedget indev
/// @param drawing 
void Wedget::SetIndev(Indev* indev)
{
	this->indev = indev;
}


/// @brief Wedget drawing
/// @param drawing 
void Wedget::SetDrawing(Drawing* drawing)
{
	this->drawing = drawing;
}


/// @brief Wedget Offset
/// @param xoff 
/// @param yoff 
void Wedget::SetOffset(int xoff, int yoff)
{
	this->xoff = xoff;
	this->yoff = yoff;
}


/// @brief 
void Wedget::InitContent()
{

}


/// @brief 
void Wedget::DrawContent()
{

}


/// @brief 
void Wedget::DrawBorder()
{
	int x0 = GetLocX();
	int y0 = GetLocY();
	int x1 = x0 + GetWidth() - 1;
	int y1 = y0 + GetHeight() - 1;
	drawing->rect.Set(x0, y0, x1, y1);
}


/// @brief Add Wedget
/// @param wedget 
/// @return 
void Wedget::AddWedget(Wedget* wedget)
{
	if (NULL != wedget) 
	{
		wedgets.Add(wedget);
	}
}


/// @brief Wedget showing
void Wedget::Showing()
{
	if ((NULL != indev) && (NULL != drawing))
	{
		InitContent();
		DrawBorder();
		DrawContent();
	}

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();
		wedget->SetIndev(indev);
		wedget->SetDrawing(drawing);
		wedget->SetOffset(GetLocX(), GetLocY());
		wedget->Showing();
	}
}


/// @brief Wedget refresh
void Wedget::Refresh()
{
	if (true == isChange)
	{
		DrawContent();
		isChange = false;
	}

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->Refresh();
	}
}


/// @brief Wedget input text
/// @param data 
/// @param size 
void Wedget::InputData(char* data, int size)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputData(data, size);
	}
}


/// @brief Wedget input axis
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Wedget::InputAxis(int axisX, int axisY, int axisZ)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputAxis(axisX, axisY, axisZ);
	}
}
