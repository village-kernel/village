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
	update(false),
	cmd(NULL)
{
}


/// @brief Destructor
Wedget::~Wedget()
{
	wedgets.Release();
}


/// @brief Wedget move in absolute position
/// @param x 
/// @param y 
void Wedget::MoveTo(int x, int y)
{
	int axisx = x - layerArea.sx;
	int axisy = y - layerArea.sy;
	AxisMove(axisx, axisy);
}


/// @brief Wedget move in relative position
/// @param axisx 
/// @param axisy 
void Wedget::AxisMove(int axisx, int axisy)
{
	layerArea.sx += axisx;
	layerArea.ex += axisx;
	layerArea.sy += axisy;
	layerArea.ey += axisy;
	
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();
		
		item->AxisMove(axisx, axisy);
	}
}


/// @brief Wedget set size
/// @param area 
void Wedget::SetSize(int width, int height)
{
	layerArea.ex = layerArea.sx + width - 1;
	layerArea.ey = layerArea.sy + height - 1;
}


/// @brief Is in area
/// @param x 
/// @param y 
/// @return 
bool Wedget::IsInArea(int x, int y)
{
	return layer.IsCoordinateInArea(x, y, layerArea);
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


/// @brief GetLayerArea
/// @return 
DrawArea Wedget::GetLayerArea()
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


/// @brief Wedget update
void Wedget::UpdateRequest(bool request)
{
	this->update = request;
}


/// @brief Wedget is update request
/// @return 
bool Wedget::IsUpdateRequest()
{
	return update;
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
		wedget->AxisMove(GetX(), GetY());
		wedgets.Add(wedget);
	}
}


/// @brief Wedget Initiate
/// @param devices 
void Wedget::Initiate(VgDevices* devices)
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
		if (NULL != cmd) cmd->Execute();
	}

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();
		
		item->Execute(input);
	}
}


/// @brief Wedget redraw wedget areas
/// @param wedget 
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawWedgetAreas(Wedget* wedget, DrawAreas areas)
{
	DrawAreas cutAreas = areas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		if (layer.IsAreaOverlap(area, wedget->GetLayerArea()))
		{
			DrawArea redraw = layer.GetOverlapArea(area, wedget->GetLayerArea());

			wedget->Redraw(redraw);

			cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);
		}
	}

	return cutAreas;
}


/// @brief Wedget Draw
/// @param drawArea 
void Wedget::Redraw(DrawArea drawArea)
{
	if (true == hidden) return;

	DrawAreas redraws; redraws.Add(drawArea);
	
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		redraws = RedrawWedgetAreas(item, redraws);
	}

	rect.Execute(layerArea, redraws, bgColor);
}


/// @brief Wedget Draw
/// @param drawAreas 
void Wedget::Redraw(DrawAreas drawAreas)
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

	Redraw(layerArea);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();
		
		item->Show();
	}
}
