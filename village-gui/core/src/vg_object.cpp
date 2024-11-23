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
	:devices(devices)
{
}


/// @brief Destructor
GraphicsObject::~GraphicsObject()
{
}


/// @brief Setup
void GraphicsObject::Setup()
{
	//Create an default window as actived window
	actWedget = Create();
}


/// @brief Execute
void GraphicsObject::Execute()
{
	IndevData input = devices.indev->Read();

	//Change actived window
	if (IsActWedgetChange(input))
	{
		RedrawActWedgetOverlapAreas();
	}
	//Move actived window
	else if (IsActWedgetMove(input))
	{
		RedrawActWedgetOverlapAreas();
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


/// @brief Is actived window change
/// @param input 
/// @return 
bool GraphicsObject::IsActWedgetChange(IndevData input)
{
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{
		if (!layer.IsCoordinateInArea(input.point.x, input.point.y, actWedget->GetArea()))
		{
			for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
			{
				Wedget* wedget = wedgets.Item();

				if (layer.IsCoordinateInArea(input.point.x, input.point.y, wedget->GetArea()))
				{
					actWedget = wedget;
					return true;
				}
			}
		}
	}
	return false;
}


/// @brief Is actived wedget move
/// @param input 
/// @return 
bool GraphicsObject::IsActWedgetMove(IndevData input)
{
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{

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


/// @brief Cut actived window overlap areas
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


/// @brief Incise actived window overlap areas
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


/// @brief Redraw actived window areas
/// @param areas 
void GraphicsObject::RedrawActWedgetArea(List<DrawArea> areas)
{
	for (areas.Begin(); !areas.IsEnd(); areas.Next())
	{
		actWedget->Drawing(areas.Item());
	}
}


/// @brief Redraw actived window overlap areas
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
