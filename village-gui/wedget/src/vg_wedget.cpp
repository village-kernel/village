//###########################################################################
// vg_wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_wedget.h"


/// @brief Constructor
Wedget::Wedget()
	:sysinfo(NULL)
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
/// @return 
int Wedget::GetX()
{
	return area.x0;
}


/// @brief 
/// @return 
int Wedget::GetY()
{
	return area.y0;
}


/// @brief GetWidth
/// @return 
int Wedget::GetWidth()
{
	return area.x1 - area.x0 + 1;
}


/// @brief GetHeight
/// @return 
int Wedget::GetHeight()
{
	return area.y1 - area.y0 + 1;
}


/// @brief GetArea
/// @return 
DrawArea Wedget::GetArea()
{
	return area;
}


/// @brief Add Wedget
/// @param wedget 
/// @return 
void Wedget::AddWedget(Wedget* wedget)
{
	if (NULL != wedget) 
	{
		wedget->Init(sysinfo);
		wedgets.Add(wedget);
	}
}



/// @brief SetCommand
/// @param cmd 
void Wedget::SetCommand(ICommand* cmd)
{
	this->cmd = cmd;
}


/// @brief Init
/// @param sysinfo 
void Wedget::Init(SystemInfo* sysinfo)
{
	this->sysinfo = sysinfo;
}


/// @brief Execute
/// @param input 
void Wedget::Execute(IndevData input)
{

}


/// @brief Wedget Flush
/// @param draws 
void Wedget::Flush(List<DrawArea> areas)
{

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
