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
	bTitle(NULL),
	bBgColor(NULL),
	bHidden(NULL),
	bEnable(NULL),
	bFixed(NULL),
	bMultiply(NULL),
	bFocus(NULL),
	bFloatable(NULL),
	bUpdata(NULL),
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


/// @brief Wedget is in area
/// @param x 
/// @param y 
/// @return 
bool Wedget::IsInArea(int x, int y)
{
	return layer.IsCoordinateInArea(x, y, layerArea);
}


/// @brief Wedget is area valid
/// @return 
bool Wedget::IsAreaValid()
{
	return layer.IsAreaVaild(layerArea);
}


/// @brief Wedget get x
/// @return 
int Wedget::GetX()
{
	return layerArea.sx;
}


/// @brief Wedget get y
/// @return 
int Wedget::GetY()
{
	return layerArea.sy;
}


/// @brief Wedget get width
/// @return 
int Wedget::GetWidth()
{
	return layerArea.ex - layerArea.sx + 1;
}


/// @brief Wedget get height
/// @return 
int Wedget::GetHeight()
{
	return layerArea.ey - layerArea.sy + 1;
}


/// @brief Wedget get layer area
/// @return 
DrawArea Wedget::GetLayerArea()
{
	return layerArea;
}


/// @brief Wedget get floatable areas
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


/// @brief Wedget get update areas
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


/// @brief Wedget redraw multiplys
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


/// @brief Wedget redraw multiply areas
/// @param areas 
/// @return 
void Wedget::RedrawMultiplyAreas(DrawAreas areas)
{
	RedrawMultiplyAreas(this, areas);
}


/// @brief Wedget redraw multiply areas
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


/// @brief Wedget binding title
/// @param title 
void Wedget::BindingTitle(IData<char*>* title)
{
	bTitle = title; if (bTitle) bTitle->Binding(this);
}


/// @brief Wedget set title
/// @param title 
void Wedget::SetTitle(char* title)
{
	this->title = title; if (bTitle) bTitle->Set(title);
}


/// @brief Wedget get title
/// @return 
char* Wedget::GetTitle()
{
	return bTitle ? bTitle->Get() : title;
}


/// @brief Wedget binding bg color
/// @param color 
void Wedget::BindingBgColor(IData<int>* color)
{
	bBgColor = color; if (bBgColor) bBgColor->Binding(this);
}


/// @brief Wedget set bg color
/// @param color 
void Wedget::SetBgColor(int color)
{
	this->bgColor = color; if (bBgColor) bBgColor->Set(color);
}


/// @brief Wedget get bg color
/// @return 
int Wedget::GetBgColor()
{
	return bBgColor ? bBgColor->Get() : bgColor;
}


/// @brief Wedget binding hidden
/// @param hidden 
void Wedget::BindingHidden(IData<bool>* hidden)
{
	bHidden = hidden; if (bHidden) bHidden->Binding(this);
}


/// @brief Wedget set hidden
/// @param hidden 
void Wedget::SetHidden(bool hidden)
{
	this->hidden = hidden; if (bHidden) bHidden->Set(hidden);
}


/// @brief Wedget is hidden
/// @return 
bool Wedget::IsHidden()
{
	return bHidden ? bHidden->Get() : hidden;
}


/// @brief Wedget binding enable 
/// @param enable 
void Wedget::BindingEnable(IData<bool>* enable)
{
	bEnable = enable; if (bEnable) bHidden->Binding(this);
}


/// @brief Wedget set enable
/// @param enable 
void Wedget::SetEnable(bool enable)
{
	this->enable = enable; if (bEnable) bEnable->Set(enable);
}


/// @brief Wedget is enable
/// @return 
bool Wedget::IsEnable()
{
	return bEnable ? bEnable->Get() : enable;
}


/// @brief Wedget binding fixed
/// @param fixed 
void Wedget::BindingFixed(IData<bool>* fixed)
{
	bFixed = fixed; if (bFixed) bFixed->Binding(this);
}


/// @brief Wedget set fixed
/// @param fixed 
void Wedget::SetFixed(bool fixed)
{
	this->fixed = fixed; if (bFixed) bFixed->Set(fixed);
}


/// @brief Wedget is fixed
/// @return 
bool Wedget::IsFixed()
{
	return bFixed ? bFixed->Get() : fixed;
}


/// @brief Wedget binding multiply
/// @param multiply 
void Wedget::BindingMultiply(IData<bool>* multiply)
{
	bMultiply = multiply; if (bMultiply) bMultiply->Binding(this);
}


/// @brief Wedget set multiply
/// @param multiply 
void Wedget::SetMultiply(bool multiply)
{
	this->multiply = multiply; if (bMultiply) bMultiply->Set(multiply);
}


/// @brief Wedget is multiply
/// @return 
bool Wedget::IsMultiply()
{
	return bMultiply ? bMultiply->Get() : multiply;
}


/// @brief Wedget binding focus
/// @param focus 
void Wedget::BindingFocus(IData<bool>* focus)
{
	bFocus = focus; if (bFocus) bFocus->Binding(this);
}


/// @brief Wedget set focus
/// @param focus 
void Wedget::SetFocus(bool focus)
{
	this->focus = focus; if (bFocus) bFocus->Set(focus);

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
	return bFocus ? bFocus->Get() : focus;
}


/// @brief Wedget binding floatable
/// @param floatable 
void Wedget::BindingFloatable(IData<bool>* floatable)
{
	bFloatable = floatable; if (bFloatable) bFloatable->Binding(this);
}


/// @brief Wedget set floatable
/// @param floatable 
void Wedget::SetFloatable(bool floatable)
{
	this->floatable = floatable; if (bFloatable) bFloatable->Set(floatable);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		item->SetFloatable(floatable);
	}
}


/// @brief Wedget is floatable
/// @return 
bool Wedget::IsFloatable()
{
	bool abled = bFloatable ? bFloatable->Get() : floatable;

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


/// @brief Wedget binding update request
/// @param request 
void Wedget::BindingUpdateRequest(IData<bool>* request)
{
	bUpdata = request; if (bUpdata) bUpdata->Binding(this);
}


/// @brief Wedget update request
void Wedget::UpdateRequest(bool request)
{
	this->update = request; if (bUpdata) bUpdata->Set(request);

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
	bool request = bUpdata ? bUpdata->Get() : update;

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


/// @brief Wedget add wedget
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
