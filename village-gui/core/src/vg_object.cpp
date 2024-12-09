//###########################################################################
// vg_object.cpp
// Definitions of the functions that manage object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_object.h"
#include "vk_event_codes.h"


/// @brief Constructor
GraphicsObject::GraphicsObject(GraphicsDevices& devices)
	:devices(devices),
	defWedget(NULL),
	actWedget(NULL)
{
}


/// @brief Destructor
GraphicsObject::~GraphicsObject()
{
}


/// @brief Setup
void GraphicsObject::Setup()
{
	//Create an default wedget
	defWedget = new Wedget();

	//Set default wedget as active wedget
	actWedget = defWedget;
}


/// @brief Execute
void GraphicsObject::Execute()
{
	//Update input
	UpdataInput();

	//Update mouse cursor
	if (IsCurWedgetMove())
	{
		RedrawMoveWedgetOverlapAreas(devices.indev->Cursor());
	}

	//Change actived wedget
	if (IsActWedgetChange())
	{
		RedrawActWedgetOverlapAreas();

		SwapActWedgetListNode();
	}
	//Move actived wedget
	else if (IsActWedgetMove())
	{
		RedrawMoveWedgetOverlapAreas(actWedget);
	}
	//Active wedget execute
	else
	{
		actWedget->Execute(input);
	}
}


/// @brief Exit
void GraphicsObject::Exit()
{
	wedgets.Release();
}


/// @brief Is actived wedget change
/// @param input 
/// @return 
bool GraphicsObject::IsActWedgetChange()
{
	if (EventCode::_BtnLeft != input.key) return false;
	
	if (KeyState::_Pressed != input.state) return false;
	
	for (wedgets.End(); !wedgets.IsBegin(); wedgets.Prev())
	{
		Wedget* wedget = wedgets.Item();

		if (layer.IsCoordinateInArea(input.point.x, input.point.y, wedget->GetArea()))
		{
			if (actWedget != wedget)
			{
				actWedget = wedget;
				return true;
			}
			break;
		}
	}
	
	return false;
}


/// @brief Get actived wedget upper areas
/// @return 
VgList<DrawArea> GraphicsObject::GetActWedgetUpperAreas()
{
	VgList<DrawArea> getAreas;

	wedgets.Begin(); while(wedgets.Item() != actWedget) { wedgets.Next(); }

	for (wedgets.Next(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();

		getAreas.Add(wedget->GetArea());
	}

	return getAreas;
}


/// @brief Redraw actived wedget overlap areas
void GraphicsObject::RedrawActWedgetOverlapAreas()
{
	VgList<DrawArea> areas;
	
	//Get active wedget upper areas
	areas = GetActWedgetUpperAreas();

	//Get overlap areas
	areas = layer.GetOverlapAreas(actWedget->GetArea(), areas);

	//Sift overlap areas
	areas = layer.SiftOverlapAreas(areas);

	//Cut overlap areas
	areas = layer.CutOverlapAreas(areas);
	
	//Incise overlap areas
	//areas = layer.InciseOverlapAreas(areas);

	//Redraw overlap areas
	actWedget->Redraw(areas);
}


/// @brief Swap active wedget
void GraphicsObject::SwapActWedgetListNode()
{
	if (false == actWedget->IsOnBottom() && 
		false == actWedget->IsOnTop())
	{
		wedgets.Remove(actWedget);
		wedgets.Add(actWedget);
	}
}


/// @brief Updata input
void GraphicsObject::UpdataInput()
{
	static IndevData last;

	input = devices.indev->Read();

	if (IndevType::_Mouse == devices.indev->GetType())
	{
		axis.point.x = input.point.x - last.point.x;
		axis.point.y = input.point.y - last.point.y;
		last = input;
	}
}


/// @brief Is cursor wedget move
/// @param input 
/// @return 
bool GraphicsObject::IsCurWedgetMove()
{
	if (IndevType::_Mouse != devices.indev->GetType())
		return false;
	if (NULL == devices.indev->Cursor())
		return false;
	return true;
}


/// @brief Is actived wedget move
/// @param input 
/// @return 
bool GraphicsObject::IsActWedgetMove()
{
	if (actWedget->IsFixed()) return false;

	if (EventCode::_BtnLeft != input.key) return false;

	if (KeyState::_Pressed != input.state) return false;

	if (layer.IsCoordinateInArea(input.point.x, input.point.y, actWedget->GetArea()))
	{
		return (axis.point.x || axis.point.y);
	}

	return false;
}


/// @brief Get move wedget overlap areas
/// @param input 
/// @return 
VgList<DrawArea> GraphicsObject::GetMoveWedgetOverlapAreas(Wedget* movWedget)
{
	DrawArea oldArea = movWedget->GetArea();
	
	movWedget->Move(axis.point.x, axis.point.y);
	
	DrawArea newArea = movWedget->GetArea();

	return layer.MovedOverlapArea(oldArea, newArea);
}


/// @brief Redraw move wedget areas
/// @param areas 
void GraphicsObject::RedrawMoveWedgetArea(Wedget* movWedget, VgList<DrawArea> areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
		{
			Wedget* wedget = wedgets.Item();

			if (wedget == movWedget) continue;

			if (layer.IsAreaOverlap(area, wedget->GetArea()))
			{
				wedget->Redraw(area);
			}
		}
	}

	movWedget->Show();
}


/// @brief Redraw move wedget overlap areas
void GraphicsObject::RedrawMoveWedgetOverlapAreas(Wedget* movWedget)
{
	VgList<DrawArea> areas;

	//Get move overlap areas
	areas = GetMoveWedgetOverlapAreas(movWedget);

	//Redraw move areas
	RedrawMoveWedgetArea(movWedget, areas);
}


/// @brief Create wedget
/// @return 
Wedget* GraphicsObject::Create()
{
	Wedget* wedget = new Wedget();
	wedget->Initiate(&devices);
	wedgets.Add(wedget);
	return wedget;
}


/// @brief Destory wedget
/// @param wedget 
/// @return 
bool GraphicsObject::Destroy(Wedget* wedget)
{
	if (NULL != wedget)
	{
		wedgets.Remove(wedget);
		delete wedget;
		return true;
	}
	return false;
}
