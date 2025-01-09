//###########################################################################
// vg_wedget.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_wedget.h"
#include "vk_event_codes.h"


/// @brief Constructor
VgWedget::VgWedget()
	:devices(NULL),
	title((char*)"wedget"),
	bgColor(VgDrawDefs::_White),
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
VgWedget::~VgWedget()
{
	wedgets.Release();
}


/// @brief Wedget move in absolute position
/// @param x 
/// @param y 
void VgWedget::MoveTo(int x, int y)
{
	int axisx = x - layerArea.sx;
	int axisy = y - layerArea.sy;
	AxisMove(axisx, axisy);
}


/// @brief Wedget move in relative position
/// @param axisx 
/// @param axisy 
void VgWedget::AxisMove(int axisx, int axisy)
{
	layerArea.sx += axisx;
	layerArea.ex += axisx;
	layerArea.sy += axisy;
	layerArea.ey += axisy;
	
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();
		
		item->AxisMove(axisx, axisy);
	}
}


/// @brief Wedget set size
/// @param area 
void VgWedget::SetSize(int width, int height)
{
	layerArea.ex = layerArea.sx + width - 1;
	layerArea.ey = layerArea.sy + height - 1;
}


/// @brief Wedget is in layer area
/// @param x 
/// @param y 
/// @return 
bool VgWedget::IsInLayerArea(int x, int y)
{
	return layer.IsCoordinateInArea(x, y, layerArea);
}


/// @brief Wedget is layer area valid
/// @return 
bool VgWedget::IsLayerAreaValid()
{
	return layer.IsAreaVaild(layerArea);
}


/// @brief Wedget get x
/// @return 
int VgWedget::GetX()
{
	return layerArea.sx;
}


/// @brief Wedget get y
/// @return 
int VgWedget::GetY()
{
	return layerArea.sy;
}


/// @brief Wedget get width
/// @return 
int VgWedget::GetWidth()
{
	return layerArea.ex - layerArea.sx + 1;
}


/// @brief Wedget get height
/// @return 
int VgWedget::GetHeight()
{
	return layerArea.ey - layerArea.sy + 1;
}


/// @brief Wedget get layer area
/// @return 
VgDrawArea VgWedget::GetLayerArea()
{
	return layerArea;
}


/// @brief Wedget get floatable areas
/// @return 
VgDrawAreas VgWedget::GetFloatAreas()
{
	VgDrawAreas areas;

	if (!hidden && floatable) areas.Add(layerArea);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		areas.Append(item->GetFloatAreas());
	}

	return areas;
}


/// @brief Wedget get update areas
/// @return 
VgDrawAreas VgWedget::GetUpdateAreas()
{
	VgDrawAreas areas;

	if (update) areas.Add(layerArea);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		areas.Append(item->GetUpdateAreas());
	}

	return areas;
}


/// @brief Wedget redraw floats
/// @param drawAreas 
/// @return 
VgDrawAreas VgWedget::RedrawFloats(VgDrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		areas = RedrawFloatAreas(item, areas);
	}

	return areas;
}


/// @brief Wedget redraw float areas
/// @param areas 
/// @return 
VgDrawAreas VgWedget::RedrawFloatAreas(VgDrawAreas areas)
{
	return RedrawFloatAreas(this, areas);
}


/// @brief Wedget redraw float areas
/// @param wedget 
/// @param areas 
/// @return 
VgDrawAreas VgWedget::RedrawFloatAreas(VgWedget* wedget, VgDrawAreas areas)
{
	if (!wedget->IsFloatable()) return areas;

	VgDrawAreas cutAreas = areas;
	VgDrawAreas flyAreas = wedget->GetFloatAreas();

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		VgDrawArea item = areas.Item();

		for (flyAreas.Begin(); !flyAreas.IsEnd(); flyAreas.Next())
		{
			VgDrawArea area = flyAreas.Item();

			if (layer.IsAreaOverlap(item, area))
			{
				VgDrawArea redraw = layer.GetOverlapArea(item, area);

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
VgDrawAreas VgWedget::RedrawWedgets(VgDrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		areas = RedrawWedgetAreas(item, areas);

		if (areas.IsEmpty()) break;
	}

	return areas;
}


/// @brief Wedget redraw wedget areas
/// @param areas 
/// @return 
VgDrawAreas VgWedget::RedrawWedgetAreas(VgDrawAreas areas)
{
	return RedrawWedgetAreas(this, areas);
}


/// @brief Wedget redraw wedget areas
/// @param wedget 
/// @param areas 
/// @return 
VgDrawAreas VgWedget::RedrawWedgetAreas(VgWedget* wedget, VgDrawAreas areas)
{
	if (wedget->IsMultiply()) return areas;

	VgDrawArea  layArea  = wedget->GetLayerArea();
	VgDrawAreas cutAreas = areas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		VgDrawArea item = areas.Item();

		if (layer.IsAreaOverlap(item, layArea))
		{
			VgDrawArea redraw = layer.GetOverlapArea(item, layArea);

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
void VgWedget::RedrawMultiplys(VgDrawAreas areas)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		if (item->IsHidden()) continue;

		RedrawMultiplyAreas(item, areas);
	}
}


/// @brief Wedget redraw multiply areas
/// @param areas 
/// @return 
void VgWedget::RedrawMultiplyAreas(VgDrawAreas areas)
{
	RedrawMultiplyAreas(this, areas);
}


/// @brief Wedget redraw multiply areas
/// @param wedget 
/// @param areas 
/// @return 
void VgWedget::RedrawMultiplyAreas(VgWedget* wedget, VgDrawAreas areas)
{
	if (!wedget->IsMultiply()) return;

	VgDrawArea layArea = wedget->GetLayerArea();

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		VgDrawArea item = areas.Item();

		if (layer.IsAreaOverlap(item, layArea))
		{
			VgDrawArea redraw = layer.GetOverlapArea(item, layArea);

			wedget->Redraw(redraw);
		}
	}
}


/// @brief Wedget redraw backgroud areas
/// @param areas 
void VgWedget::RedrawBackgroundAreas(VgDrawAreas areas)
{
	drawRect.Execute(layerArea, areas, bgColor);
}


/// @brief Wedget binding title
/// @param title 
void VgWedget::BindingTitle(IData<char*>* title)
{
	bTitle = title; if (bTitle) bTitle->Binding(this);
}


/// @brief Wedget set title
/// @param title 
void VgWedget::SetTitle(char* title)
{
	this->title = title; if (bTitle) bTitle->Set(title);
}


/// @brief Wedget get title
/// @return 
char* VgWedget::GetTitle()
{
	return bTitle ? bTitle->Get() : title;
}


/// @brief Wedget binding bg color
/// @param color 
void VgWedget::BindingBgColor(IData<int>* color)
{
	bBgColor = color; if (bBgColor) bBgColor->Binding(this);
}


/// @brief Wedget set bg color
/// @param color 
void VgWedget::SetBgColor(int color)
{
	this->bgColor = color; if (bBgColor) bBgColor->Set(color);
}


/// @brief Wedget get bg color
/// @return 
int VgWedget::GetBgColor()
{
	return bBgColor ? bBgColor->Get() : bgColor;
}


/// @brief Wedget binding hidden
/// @param hidden 
void VgWedget::BindingHidden(IData<bool>* hidden)
{
	bHidden = hidden; if (bHidden) bHidden->Binding(this);
}


/// @brief Wedget set hidden
/// @param hidden 
void VgWedget::SetHidden(bool hidden)
{
	this->hidden = hidden; if (bHidden) bHidden->Set(hidden);
}


/// @brief Wedget is hidden
/// @return 
bool VgWedget::IsHidden()
{
	return bHidden ? bHidden->Get() : hidden;
}


/// @brief Wedget binding enable 
/// @param enable 
void VgWedget::BindingEnable(IData<bool>* enable)
{
	bEnable = enable; if (bEnable) bHidden->Binding(this);
}


/// @brief Wedget set enable
/// @param enable 
void VgWedget::SetEnable(bool enable)
{
	this->enable = enable; if (bEnable) bEnable->Set(enable);
}


/// @brief Wedget is enable
/// @return 
bool VgWedget::IsEnable()
{
	return bEnable ? bEnable->Get() : enable;
}


/// @brief Wedget binding fixed
/// @param fixed 
void VgWedget::BindingFixed(IData<bool>* fixed)
{
	bFixed = fixed; if (bFixed) bFixed->Binding(this);
}


/// @brief Wedget set fixed
/// @param fixed 
void VgWedget::SetFixed(bool fixed)
{
	this->fixed = fixed; if (bFixed) bFixed->Set(fixed);
}


/// @brief Wedget is fixed
/// @return 
bool VgWedget::IsFixed()
{
	return bFixed ? bFixed->Get() : fixed;
}


/// @brief Wedget binding multiply
/// @param multiply 
void VgWedget::BindingMultiply(IData<bool>* multiply)
{
	bMultiply = multiply; if (bMultiply) bMultiply->Binding(this);
}


/// @brief Wedget set multiply
/// @param multiply 
void VgWedget::SetMultiply(bool multiply)
{
	this->multiply = multiply; if (bMultiply) bMultiply->Set(multiply);
}


/// @brief Wedget is multiply
/// @return 
bool VgWedget::IsMultiply()
{
	return bMultiply ? bMultiply->Get() : multiply;
}


/// @brief Wedget binding focus
/// @param focus 
void VgWedget::BindingFocus(IData<bool>* focus)
{
	bFocus = focus; if (bFocus) bFocus->Binding(this);
}


/// @brief Wedget set focus
/// @param focus 
void VgWedget::SetFocus(bool focus)
{
	this->focus = focus; if (bFocus) bFocus->Set(focus);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		item->SetFocus(focus);
	}
}


/// @brief Wedget is focus
/// @return 
bool VgWedget::IsFocus()
{
	return bFocus ? bFocus->Get() : focus;
}


/// @brief Wedget binding floatable
/// @param floatable 
void VgWedget::BindingFloatable(IData<bool>* floatable)
{
	bFloatable = floatable; if (bFloatable) bFloatable->Binding(this);
}


/// @brief Wedget set floatable
/// @param floatable 
void VgWedget::SetFloatable(bool floatable)
{
	this->floatable = floatable; if (bFloatable) bFloatable->Set(floatable);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		item->SetFloatable(floatable);
	}
}


/// @brief Wedget is floatable
/// @return 
bool VgWedget::IsFloatable()
{
	bool abled = bFloatable ? bFloatable->Get() : floatable;

	if (!abled)
	{
		for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
		{
			VgWedget* item = wedgets.Item();

			abled = item->IsFloatable();

			if (abled) break;
		}
	}

	return abled;
}


/// @brief Wedget binding update request
/// @param request 
void VgWedget::BindingUpdateRequest(IData<bool>* request)
{
	bUpdata = request; if (bUpdata) bUpdata->Binding(this);
}


/// @brief Wedget update request
void VgWedget::UpdateRequest(bool request)
{
	this->update = request; if (bUpdata) bUpdata->Set(request);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();

		item->UpdateRequest(request);
	}
}


/// @brief Wedget is update request
/// @return 
bool VgWedget::IsUpdateRequest()
{
	bool request = bUpdata ? bUpdata->Get() : update;

	if (!request)
	{
		for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
		{
			VgWedget* item = wedgets.Item();

			request = item->IsUpdateRequest();

			if (request) break;
		}
	}

	return request;
}


/// @brief Wedget BindingCommand
/// @param cmd 
void VgWedget::BindingCommand(ICommand* cmd)
{
	this->cmd = cmd;
}


/// @brief Wedget execute command
/// @param args 
void VgWedget::ExecuteCommand(VgInputData input, void* args)
{
	static bool isPressed = false;

	if (EventCode::_BtnLeft == input.key)
	{
		if (!isPressed && VgKeyState::_Pressed == input.state)
		{
			isPressed = true; if (NULL != cmd) cmd->Execute(args);
		}
		else if (VgKeyState::_Released == input.state)
		{
			isPressed = false;
		}
	}
}


/// @brief Wedget add wedget
/// @param wedget 
/// @return 
void VgWedget::AddWedget(VgWedget* wedget)
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
void VgWedget::Initiate(VgDevices* devices)
{
	this->devices = devices;

	InitContent(devices);

	drawRect.Initiate(devices);
}


/// @brief Wedget Execute
/// @param input 
void VgWedget::Execute(VgInputData input)
{
	if (true == hidden) return;

	ExecContent(input);

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		VgWedget* item = wedgets.Item();
		
		item->Execute(input);
	}
}


/// @brief Wedget Draw area
/// @param drawArea 
void VgWedget::Redraw(VgDrawArea drawArea)
{
	if (true == hidden) return;

	VgDrawAreas redraws, multiplys;
	
	redraws.Add(drawArea);

	redraws = multiplys = RedrawFloats(redraws);

	redraws = RedrawWedgets(redraws);

	RedrawBackgroundAreas(redraws);

	RedrawMultiplys(multiplys);

	DrawContent(drawArea);
}


/// @brief Wedget Draw areas
/// @param drawAreas 
void VgWedget::Redraw(VgDrawAreas drawAreas)
{
	for (drawAreas.Begin(); !drawAreas.IsEnd(); drawAreas.Next())
	{
		Redraw(drawAreas.Item());
	}
}


/// @brief Wedget Show
void VgWedget::Show()
{
	Redraw(layerArea);
}
