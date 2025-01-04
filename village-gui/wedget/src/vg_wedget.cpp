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
	title((char*)"wedget"),
	bgColor(DrawDefs::_White),
	hidden(false),
	enable(true),
	fixed(false),
	multiply(false),
	focus(false),
	floatable(false),
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


/// @brief Is area valid
/// @return 
bool Wedget::IsAreaValid()
{
	return layer.IsAreaVaild(layerArea);
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


/// @brief Get layer area
/// @return 
DrawArea Wedget::GetLayerArea()
{
	return layerArea;
}


/// @brief Get floatable areas
/// @return 
DrawAreas Wedget::GetFloatAreas()
{
	DrawAreas areas;

	if (!hidden && floatable) areas.Add(layerArea);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		areas.Append(item->GetFloatAreas());
	}

	return areas;
}


/// @brief Get update areas
/// @return 
DrawAreas Wedget::GetUpdateAreas()
{
	DrawAreas areas;

	if (update) areas.Add(layerArea);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		areas.Append(item->GetUpdateAreas());
	}

	return areas;
}


/// @brief Wedget redraw floats
/// @param drawAreas 
/// @return 
DrawAreas Wedget::RedrawFloats(DrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		areas = RedrawFloatAreas(item, areas);
	}

	return areas;
}


/// @brief Wedget redraw float areas
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawFloatAreas(DrawAreas areas)
{
	return RedrawFloatAreas(this, areas);
}


/// @brief Wedget redraw float areas
/// @param wedget 
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawFloatAreas(Wedget* wedget, DrawAreas areas)
{
	if (!wedget->IsFloatable()) return areas;

	DrawAreas cutAreas = areas;
	DrawAreas flyAreas = wedget->GetFloatAreas();

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea item = areas.Item();

		for (flyAreas.Begin(); !flyAreas.IsEnd(); flyAreas.Next())
		{
			DrawArea area = flyAreas.Item();

			if (layer.IsAreaOverlap(item, area))
			{
				DrawArea redraw = layer.GetOverlapArea(item, area);

				wedget->Redraw(redraw);

				cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);
			}
		}
	}

	return cutAreas;
}


/// @brief Wedget redraw wedgets
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawWedgets(DrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		areas = RedrawWedgetAreas(item, areas);

		if (areas.IsEmpty()) break;
	}

	return areas;
}


/// @brief Wedget redraw wedget areas
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawWedgetAreas(DrawAreas areas)
{
	return RedrawWedgetAreas(this, areas);
}


/// @brief Wedget redraw wedget areas
/// @param wedget 
/// @param areas 
/// @return 
DrawAreas Wedget::RedrawWedgetAreas(Wedget* wedget, DrawAreas areas)
{
	if (wedget->IsMultiply()) return areas;

	DrawArea  layArea  = wedget->GetLayerArea();
	DrawAreas cutAreas = areas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea item = areas.Item();

		if (layer.IsAreaOverlap(item, layArea))
		{
			DrawArea redraw = layer.GetOverlapArea(item, layArea);

			wedget->Redraw(redraw);

			cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);

			if (cutAreas.IsEmpty()) break;
		}
	}

	return cutAreas;
}


/// @brief Redraw multiplys
/// @param areas 
/// @return 
void Wedget::RedrawMultiplys(DrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		RedrawMultiplyAreas(item, areas);
	}
}


/// @brief Redraw multiply areas
/// @param areas 
/// @return 
void Wedget::RedrawMultiplyAreas(DrawAreas areas)
{
	RedrawMultiplyAreas(this, areas);
}


/// @brief Redraw multiply areas
/// @param wedget 
/// @param areas 
/// @return 
void Wedget::RedrawMultiplyAreas(Wedget* wedget, DrawAreas areas)
{
	if (!wedget->IsMultiply()) return;

	DrawArea layArea = wedget->GetLayerArea();

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea item = areas.Item();

		if (layer.IsAreaOverlap(item, layArea))
		{
			DrawArea redraw = layer.GetOverlapArea(item, layArea);

			wedget->Redraw(redraw);
		}
	}
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


/// @brief Wedget set multiply
/// @param multiply 
void Wedget::SetMultiply(bool multiply)
{
	this->multiply = multiply;
}


/// @brief Wedget is multiply
/// @return 
bool Wedget::IsMultiply()
{
	return multiply;
}


/// @brief Wedget set focus
/// @param focus 
void Wedget::SetFocus(bool focus)
{
	this->focus = focus;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		item->SetFocus(focus);
	}
}


/// @brief Wedget is focus
/// @return 
bool Wedget::IsFocus()
{
	return focus;
}


/// @brief Wedget set floatable
/// @param floatable 
void Wedget::SetFloatable(bool floatable)
{
	this->floatable = floatable;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		item->SetFloatable(floatable);
	}
}


/// @brief Is floatable
/// @return 
bool Wedget::IsFloatable()
{
	bool abled = floatable;

	if (!abled)
	{
		for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
		{
			Wedget* item = wedgets.Item();

			abled = item->IsFloatable();

			if (abled) break;
		}
	}

	return abled;
}


/// @brief Wedget update
void Wedget::UpdateRequest(bool request)
{
	this->update = request;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		item->UpdateRequest(request);
	}
}


/// @brief Wedget is update request
/// @return 
bool Wedget::IsUpdateRequest()
{
	bool request = update;

	if (!request)
	{
		for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
		{
			Wedget* item = wedgets.Item();

			request = item->IsUpdateRequest();

			if (request) break;
		}
	}

	return request;
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


/// @brief Wedget Draw
/// @param drawArea 
void Wedget::Redraw(DrawArea drawArea)
{
	if (true == hidden) return;

	DrawAreas redraws; 
	
	redraws.Add(drawArea);

	redraws = RedrawFloats(redraws);

	DrawAreas multiplys = redraws;

	redraws = RedrawWedgets(redraws);

	rect.Execute(layerArea, redraws, bgColor);

	RedrawMultiplys(multiplys);
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
	Redraw(layerArea);
}
