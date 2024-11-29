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
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{
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
	}
	return false;
}


/// @brief Get actived wedget overlap areas
/// @return 
List<DrawArea> GraphicsObject::GetActWedgetOverlapAreas()
{
	List<DrawArea> getAreas;

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		Wedget* wedget = wedgets.Item();

		if (actWedget != wedget)
		{
			if (layer.IsAreaOverlap(actWedget->GetArea(), wedget->GetArea()))
			{
				getAreas.Add(layer.GetOverlapArea(actWedget->GetArea(), wedget->GetArea()));
			}
		}
	}

	return getAreas;
}


/// @brief Cut actived wedget overlap areas
/// @param areas 
/// @return 
List<DrawArea> GraphicsObject::CutActWedgetOverlapAreas(List<DrawArea> areas)
{
	List<DrawArea> cutAreas;
	List<DrawArea> tempAreas = areas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		for (tempAreas.Begin(); !tempAreas.IsEnd(); tempAreas.Next())
		{
			if (layer.IsAreaOverlap(area, tempAreas.Item()))
			{
				area = layer.CutOverlapArea(area, tempAreas.Item());
			}
		}

		cutAreas.Add(area);
	}

	return cutAreas;
}


/// @brief Incise actived wedget overlap areas
/// @param areas 
/// @return 
List<DrawArea> GraphicsObject::InciseActWedgetOverlapAreas(List<DrawArea> areas)
{
	List<DrawArea> inciseAreas;
	List<DrawArea> tempAreas = areas;

	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		DrawArea area = areas.Item();

		for (tempAreas.Begin(); !tempAreas.IsEnd(); tempAreas.Next())
		{
			DrawArea temp = tempAreas.Item();

			if (layer.IsAreaOverlap(area, temp))
			{
				List<DrawArea> list = layer.InciseOverlapArea(area, temp);

				if (0 != list.GetSize())
				{
					inciseAreas.Append(list);
				}
				else inciseAreas.Add(area);
			}
		}
	}
	
	return inciseAreas;
}


/// @brief Redraw actived wedget areas
/// @param areas 
void GraphicsObject::RedrawActWedgetArea(List<DrawArea> areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		actWedget->Redraw(areas.Item());
	}
}


/// @brief Redraw actived wedget overlap areas
void GraphicsObject::RedrawActWedgetOverlapAreas()
{
	List<DrawArea> areas;
	
	//Get overlap areas
	areas = GetActWedgetOverlapAreas();

	//Cut overlap areas
	areas = CutActWedgetOverlapAreas(areas);

	//Incise overlap areas
	areas = InciseActWedgetOverlapAreas(areas);

	//Redraw overlap areas
	RedrawActWedgetArea(areas);
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
	return ((IndevType::_Mouse == devices.indev->GetType()) && (NULL != devices.indev->Cursor()));
}


/// @brief Is actived wedget move
/// @param input 
/// @return 
bool GraphicsObject::IsActWedgetMove()
{
	if (actWedget->IsFixed()) return false;

	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{
		if (layer.IsCoordinateInArea(input.point.x, input.point.y, actWedget->GetArea()))
		{
			return (axis.point.x || axis.point.y);
		}
	}

	return false;
}


/// @brief Get move wedget overlap areas
/// @param input 
/// @return 
List<DrawArea> GraphicsObject::GetMoveWedgetOverlapAreas(Wedget* movWedget)
{
	DrawArea oldArea = movWedget->GetArea();
	
	movWedget->Move(axis.point.x, axis.point.y);
	
	DrawArea newArea = movWedget->GetArea();

	return layer.MovedOverlapArea(oldArea, newArea);
}


/// @brief Redraw move wedget areas
/// @param areas 
void GraphicsObject::RedrawMoveWedgetArea(Wedget* movWedget, List<DrawArea> areas)
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
	List<DrawArea> areas;

	//Get move overlap areas
	areas = GetMoveWedgetOverlapAreas(movWedget);

	//Redraw overlap areas
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
