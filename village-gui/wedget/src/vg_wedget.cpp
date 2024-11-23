//###########################################################################
// vg_wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_wedget.h"


/// @brief Constructor
Wedget::Wedget()
	:devices(NULL)
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
	layerArea.x0 = x;
	layerArea.x1 = x + width - 1;
	layerArea.y0 = y;
	layerArea.y1 = y + height - 1;
}


/// @brief 
/// @return 
int Wedget::GetX()
{
	return layerArea.x0;
}


/// @brief 
/// @return 
int Wedget::GetY()
{
	return layerArea.y0;
}


/// @brief GetWidth
/// @return 
int Wedget::GetWidth()
{
	return layerArea.x1 - layerArea.x0 + 1;
}


/// @brief GetHeight
/// @return 
int Wedget::GetHeight()
{
	return layerArea.y1 - layerArea.y0 + 1;
}


/// @brief GetArea
/// @return 
DrawArea Wedget::GetArea()
{
	return layerArea;
}


/// @brief Add wedget
/// @param wedget 
/// @return 
void Wedget::AddWedget(Wedget* wedget)
{
	if (NULL != wedget) 
	{
		wedget->Initiate(devices);
		wedgets.Add(wedget);
	}
}


/// @brief Show wedgets
void Wedget::ShowWedgets()
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();
		wedget->Show();
	}
}


/// @brief Wedget SetCommand
/// @param cmd 
void Wedget::SetCommand(ICommand* cmd)
{
	this->cmd = cmd;
}


/// @brief Wedget Initiate
/// @param devices 
void Wedget::Initiate(GraphicsDevices* devices)
{
	this->devices = devices;

	rect.Initiate(devices);
	mask.Initiate(devices);
}


/// @brief Wedget Execute
/// @param input 
void Wedget::Execute(IndevData input)
{

}


/// @brief Wedget Show
void Wedget::Show()
{
	Drawing(layerArea);
	ShowWedgets();
}


/// @brief Wedget Drawing
/// @param drawArea 
void Wedget::Drawing(DrawArea drawArea)
{
	rect.Execute(layerArea, drawArea, DrawDefs::White);
	mask.Execute(layerArea, drawArea, DrawDefs::Black);
}
