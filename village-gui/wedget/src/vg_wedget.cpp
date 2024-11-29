//###########################################################################
// vg_wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_wedget.h"


/// @brief Constructor
Wedget::Wedget()
	:devices(NULL),
	title((char*)"None"),
	bgColor(DrawDefs::White),
	hidden(false),
	enable(true),
	fixed(false),
	bottom(false),
	top(false)
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief Wedget set size
/// @param area 
void Wedget::SetSize(int x, int y, int width, int height)
{
	layerArea.x0 = x;
	layerArea.x1 = x + width - 1;
	layerArea.y0 = y;
	layerArea.y1 = y + height - 1;
}


/// @brief Wedget move
/// @param x 
/// @param y 
void Wedget::Move(int axisx, int axisy)
{
	layerArea.x0 += axisx;
	layerArea.x1 += axisx;
	layerArea.y0 += axisy;
	layerArea.y1 += axisy;
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


/// @brief Set title
/// @param title 
void Wedget::SetTitle(char* title)
{
	this->title = title;
}


/// @brief Get title
/// @return 
char* Wedget::GetTitle()
{
	return title;
}


/// @brief Wedget set bg color
/// @param color 
void Wedget::SetBgColor(int color)
{
	this->bgColor = color;
}


/// @brief Wedget get bg color
/// @return 
int Wedget::GetBgColor()
{
	return bgColor;
}


/// @brief Wedget set hidden
/// @param hidden 
void Wedget::SetHidden(bool hidden)
{
	this->hidden = hidden;
}


/// @brief Wedget is hidden
/// @return 
bool Wedget::IsHidden()
{
	return hidden;
}


/// @brief Wedget set enable
/// @param enable 
void Wedget::SetEnable(bool enable)
{
	this->enable = enable;
}


/// @brief Wedget is enable
/// @return 
bool Wedget::IsEnable()
{
	return enable;
}


/// @brief Wedget set fixed
/// @param fixed 
void Wedget::SetFixed(bool fixed)
{
	this->fixed = fixed;
}


/// @brief Wedget is fixed
/// @return 
bool Wedget::IsFixed()
{
	return fixed;
}


/// @brief Set on bottom
void Wedget::SetOnBottom(bool bottom)
{
	this->bottom = bottom;
}


/// @brief Is on bottom
/// @return 
bool Wedget::IsOnBottom()
{
	return bottom;
}


/// @brief Set on top
void Wedget::SetOnTop(bool top)
{
	this->top = top;
}


/// @brief Is on top
/// @return 
bool Wedget::IsOnTop()
{
	return top;
}


/// @brief Wedget BindingCommand
/// @param cmd 
void Wedget::BindingCommand(ICommand* cmd)
{
	this->cmd = cmd;
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


/// @brief Draw wedgets
void Wedget::DrawWedgets(DrawArea drawArea)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();
		
		wedget->Redraw(drawArea);
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


/// @brief Wedget Initiate
/// @param devices 
void Wedget::Initiate(GraphicsDevices* devices)
{
	this->devices = devices;

	rect.Initiate(devices);
}


/// @brief Wedget Execute
/// @param input 
void Wedget::Execute(IndevData input)
{

}


/// @brief Wedget Draw
/// @param drawArea 
void Wedget::Redraw(DrawArea drawArea)
{
	if (true == hidden) return;

	rect.Execute(layerArea, drawArea, bgColor);

	DrawWedgets(drawArea);
}


/// @brief Wedget Show
void Wedget::Show()
{
	if (true == hidden) return;

	rect.Execute(layerArea, layerArea, bgColor);
	
	ShowWedgets();
}
