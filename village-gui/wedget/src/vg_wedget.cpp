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
	bgColor(DrawDefs::_White),
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
	layerArea.sx = x;
	layerArea.ex = x + width - 1;
	layerArea.sy = y;
	layerArea.ey = y + height - 1;
}


/// @brief Wedget move
/// @param x 
/// @param y 
void Wedget::Move(int axisx, int axisy)
{
	layerArea.sx += axisx;
	layerArea.ex += axisx;
	layerArea.sy += axisy;
	layerArea.ey += axisy;
}


/// @brief 
/// @return 
int Wedget::GetX()
{
	return layerArea.sx;
}


/// @brief 
/// @return 
int Wedget::GetY()
{
	return layerArea.sy;
}


/// @brief GetWidth
/// @return 
int Wedget::GetWidth()
{
	return layerArea.ex - layerArea.sx + 1;
}


/// @brief GetHeight
/// @return 
int Wedget::GetHeight()
{
	return layerArea.ey - layerArea.sy + 1;
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


/// @brief Execite wedgets
/// @param input 
void Wedget::ExecuteWedgets(IndevData input)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();
		
		wedget->Execute(input);
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
	if (true == hidden) return;

	if (layer.IsCoordinateInArea(input.point.x, input.point.y, layerArea))
	{
		ExecuteWedgets(input);
	}
}


/// @brief Wedget Draw
/// @param drawArea 
void Wedget::Redraw(DrawArea drawArea)
{
	if (true == hidden) return;

	rect.Execute(layerArea, drawArea, bgColor);

	DrawWedgets(drawArea);
}


/// @brief Wedget Draw
/// @param drawAreas 
void Wedget::Redraw(VgList<DrawArea> drawAreas)
{
	for (drawAreas.Begin(); !drawAreas.IsEnd(); drawAreas.Next())
	{
		Redraw(drawAreas.Item());
	}
}


/// @brief Wedget Show
void Wedget::Show()
{
	if (true == hidden) return;

	rect.Execute(layerArea, layerArea, bgColor);
	
	ShowWedgets();
}
