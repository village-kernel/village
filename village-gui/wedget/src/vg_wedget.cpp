//###########################################################################
// vg_wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_wedget.h"


/// @brief Constructor
Wedget::Wedget()
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief Wedget Setup
/// @param area 
void Wedget::SetSize(int x, int y, int width, int height)
{
	area.x0 = x;
	area.x1 = x + width - 1;
	area.y0 = y;
	area.y1 = y + height - 1;
}


/// @brief 
/// @param x 
/// @param y 
/// @return 
bool Wedget::IsCanSelecte(int x, int y)
{
	return (x >= area.x0 && x <= area.x1 && y >= area.y0 && y <= area.y1);
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


/// @brief Wedget Show
void Wedget::Show()
{
	InitContent();
	DrawContent();

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();
		wedget->Show();
	}
}
