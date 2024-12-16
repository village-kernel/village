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
		RedrawSelWedgetOverlapAreas(actWedget);

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


/// @brief Is actived wedget change
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


/// @brief Swap active wedget
void GraphicsObject::SwapActWedgetListNode()
{
	if (false == actWedget->IsOnBottom() && 
		false == actWedget->IsOnTop())
	{
		wedgets.Remove(actWedget);
		wedgets.Add(actWedget);
	}

	if (actWedget->IsAlwaysFocus())
	{
		actWedget->Execute(input);
	}
}


/// @brief Get wedget upper areas
/// @return 
DrawAreas GraphicsObject::GetWedgetUpperAreas()
{
	DrawAreas getAreas;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();

		if (wedget->IsOnTop())
		{
			getAreas.Add(wedget->GetArea());
		}	
	}

	return getAreas;
}


/// @brief Get selected wedget overlap areas
/// @return 
DrawAreas GraphicsObject::GetSelWedgetOverlapAreas(Wedget* selWedget)
{
	DrawAreas getAreas;

	wedgets.Begin(); while(wedgets.Item() != selWedget) { wedgets.Next(); }

	for (wedgets.Next(); !wedgets.IsEnd(); wedgets.Next())
	{
		getAreas.Add(wedgets.Item()->GetArea());
	}

	return getAreas;
}


/// @brief Get moved wedget overlap areas
/// @param input 
/// @return 
DrawAreas GraphicsObject::GetMoveWedgetOverlapAreas(Wedget* movWedget)
{
	DrawArea oldArea = movWedget->GetArea();
	
	movWedget->Move(axis.point.x, axis.point.y);
	
	DrawArea newArea = movWedget->GetArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw actived wedget overlap areas
/// @param wedget 
void GraphicsObject::RedrawSelWedgetOverlapAreas(Wedget* selWedget)
{
	//Get upper areas
	DrawAreas upperAreas = GetWedgetUpperAreas();

	//Get overlap areas
	DrawAreas overlapAreas = GetSelWedgetOverlapAreas(selWedget);

	//Calc redraw areas
	DrawAreas redrawAreas = layer.CalcOverlapAreas(selWedget->GetArea(), overlapAreas, upperAreas);

	//Wedget redraw
	selWedget->Redraw(redrawAreas);
}


/// @brief Redraw move wedget overlap areas
void GraphicsObject::RedrawMoveWedgetOverlapAreas(Wedget* movWedget)
{
	//Get move overlap areas
	DrawAreas movAreas = GetMoveWedgetOverlapAreas(movWedget);

	//Redraw other wedget areas
	for (wedgets.End(); !wedgets.IsBegin(); wedgets.Prev())
	{
		Wedget* wedget = wedgets.Item();

		if (wedget == movWedget) continue;

		DrawAreas cutAreas = movAreas;

		for (movAreas.Begin(); !movAreas.IsEnd(); movAreas.Next())
		{
			DrawArea area = movAreas.Item();

			if (layer.IsAreaOverlap(area, wedget->GetArea()))
			{
				DrawArea redraw = layer.GetOverlapArea(area, wedget->GetArea());

				wedget->Redraw(redraw);

				cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);
			}
		}

		movAreas = cutAreas;
	}

	//Redraw moved wedget areas
	if (devices.indev->Cursor() != movWedget)
	{
		DrawArea cursorArea = devices.indev->Cursor()->GetArea();
		DrawArea movWedArea = movWedget->GetArea();
		DrawAreas areas = layer.CutOverlapAreas(movWedArea, cursorArea);
		movWedget->Redraw(areas);
	}
	else
	{
		movWedget->Show();
	}
}
