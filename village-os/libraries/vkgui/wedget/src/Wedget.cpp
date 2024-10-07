//###########################################################################
// Wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Wedget.h"


/// @brief Constructor
Wedget::Wedget()
	:drawing(NULL),
	x(0),
	y(0),
	xoff(0),
	yoff(0),
	width(0),
	height(0),
	isChange(false)
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief Wedget Setup
/// @param drawing 
void Wedget::Setup(Drawing* drawing, Indev* indev)
{
	this->drawing = drawing;
	this->indev = indev;
}


/// @brief Wedget Offset
/// @param xoff 
/// @param yoff 
void Wedget::Offset(int xoff, int yoff)
{
	this->xoff = xoff;
	this->yoff = yoff;
}


/// @brief Wedget Resize
/// @param x 
/// @param y 
/// @param width 
/// @param height 
void Wedget::Resize(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
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
