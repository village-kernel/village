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
	actWedget(NULL),
	curWedget(NULL)
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
		curWedget = devices.indev->Cursor();

		RedrawOtherWedgetAreas(curWedget);

		RedrawMoveWedgetAreas(curWedget);
	}

	//Change actived wedget
	if (IsActWedgetChange())
	{
		RedrawSelWedgetOverlapAreas(actWedget);

		SwapActWedgetListNode(actWedget);

		AlwaysFocusWedgetExecute(actWedget);
	}
	//Move actived wedget
	else if (IsActWedgetMove())
	{
		RedrawOtherWedgetAreas(actWedget);

		RedrawMoveWedgetAreas(actWedget);
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
		Wedget* item = wedgets.Item();

		if (layer.IsCoordinateInArea(input.point.x, input.point.y, item->GetArea()))
		{
			if (actWedget != item)
			{
				actWedget = item;
				return true;
			}
			break;
		}
	}
	
	return false;
}


/// @brief Get wedget upper areas
/// @param wedget 
/// @return 
DrawAreas GraphicsObject::GetWedgetUpperAreas(Wedget* wedget)
{
	DrawAreas areas;

	if (wedget == curWedget) return areas;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* item = wedgets.Item();

		if (item->IsOnTop())
		{
			areas.Add(item->GetArea());
		}	
	}

	return areas;
}


/// @brief Get selected wedget overlap areas
/// @param wedget 
/// @return 
DrawAreas GraphicsObject::GetSelWedgetOverlapAreas(Wedget* wedget)
{
	DrawAreas areas;

	wedgets.Begin(); while(wedgets.Item() != wedget) { wedgets.Next(); }

	for (wedgets.Next(); !wedgets.IsEnd(); wedgets.Next())
	{
		areas.Add(wedgets.Item()->GetArea());
	}

	return areas;
}


/// @brief Redraw actived wedget overlap areas
/// @param wedget 
void GraphicsObject::RedrawSelWedgetOverlapAreas(Wedget* wedget)
{
	//Get upper areas
	DrawAreas upper = GetWedgetUpperAreas(wedget);

	//Get overlap areas
	DrawAreas overlap = GetSelWedgetOverlapAreas(wedget);

	//Calc redraw areas
	DrawAreas redraw = layer.CalcOverlapAreas(wedget->GetArea(), overlap, upper);

	//Wedget redraw
	wedget->Redraw(redraw);
}


/// @brief Swap active wedget
/// @param wedget 
void GraphicsObject::SwapActWedgetListNode(Wedget* wedget)
{
	if (false == wedget->IsOnBottom() && 
		false == wedget->IsOnTop())
	{
		wedgets.Remove(wedget);
		wedgets.Add(wedget);
	}
}


/// @brief Execute always focus actived wedget
/// @param wedget 
void GraphicsObject::AlwaysFocusWedgetExecute(Wedget* wedget)
{
	if (wedget->IsAlwaysFocus())
	{
		wedget->Execute(input);
	}
}


/// @brief Get moved wedget overlap areas
/// @param wedget 
/// @return 
DrawAreas GraphicsObject::GetMoveWedgetOverlapAreas(Wedget* wedget)
{
	DrawArea oldArea = wedget->GetArea();
	
	wedget->Move(axis.point.x, axis.point.y);
	
	DrawArea newArea = wedget->GetArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw move wedget overlap areas
/// @param wedget 
void GraphicsObject::RedrawOtherWedgetAreas(Wedget* wedget)
{
	//Get move overlap areas
	DrawAreas movAreas = GetMoveWedgetOverlapAreas(wedget);

	//Redraw other wedget areas
	for (wedgets.End(); !wedgets.IsBegin(); wedgets.Prev())
	{
		Wedget* item = wedgets.Item();

		if (item == wedget) continue;

		DrawAreas cutAreas = movAreas;

		for (movAreas.Begin(); !movAreas.IsEnd(); movAreas.Next())
		{
			DrawArea area = movAreas.Item();

			if (layer.IsAreaOverlap(area, item->GetArea()))
			{
				DrawArea redraw = layer.GetOverlapArea(area, item->GetArea());

				item->Redraw(redraw);

				cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);
			}
		}

		movAreas = cutAreas;
	}
}


/// @brief Redraw move wedget self areas
/// @param wedget 
void GraphicsObject::RedrawMoveWedgetAreas(Wedget* wedget)
{
	//Get upper areas
	DrawAreas upper = GetWedgetUpperAreas(wedget);

	//Get overlap areas
	DrawAreas overlap; overlap.Add(wedget->GetArea());

	//Calc redraw areas
	DrawAreas redraw = layer.CalcOverlapAreas(wedget->GetArea(), overlap, upper);

	//Wedget redraw
	wedget->Redraw(redraw);
}
