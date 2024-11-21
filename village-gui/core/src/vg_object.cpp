//###########################################################################
// vg_object.cpp
// Definitions of the functions that manage object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_object.h"
#include "vk_event_codes.h"


/// @brief Constructor
GraphicsObject::GraphicsObject(SystemInfo& sysinfo)
	:sysinfo(sysinfo)
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
	activedwin = Create();
}


/// @brief Execute
void GraphicsObject::Execute()
{
	IndevData input;

	while (sysinfo.input.Pop(&input))
	{
		//Change actived window
		if (IsActivedWinChange(input))
		{
			RedrawActivedWinOverlapAreas();
		}
		//Move actived window
		else if (IsActivedWinMove(input))
		{
			RedrawActivedWinOverlapAreas();
		}
		//Active win execute
		else
		{
			activedwin->Execute(input);
		}
	}
}


/// @brief Exit
void GraphicsObject::Exit()
{
	mainwins.Release();
}


/// @brief Is actived window change
/// @param input 
/// @return 
bool GraphicsObject::IsActivedWinChange(IndevData input)
{
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{
		if (!layer.IsCoordinateInArea(input.point.x, input.point.y, activedwin->GetArea()))
		{
			for (mainwins.Begin(); !mainwins.IsEnd(); mainwins.Next())
			{
				Window* win = mainwins.Item();

				if (layer.IsCoordinateInArea(input.point.x, input.point.y, win->GetArea()))
				{
					activedwin = win;
					return true;
				}
			}
		}
	}
	return false;
}


/// @brief Is actived window move
/// @param input 
/// @return 
bool GraphicsObject::IsActivedWinMove(IndevData input)
{
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{

	}
	return false;
}


/// @brief Calc actived window redraw areas
void GraphicsObject::RedrawActivedWinOverlapAreas()
{
	List<DrawArea> areas;
	
	//Get overlap areas
	areas = GetActivedWinOverlapAreas();

	//Cut overlap areas
	areas = CutActivedWinOverlapAreas(areas);

	//Incise overlap areas
	areas = InciseActivedWinOverlapAreas(areas);

	//Redraw overlap areas
	activedwin->Flush(areas);
}


/// @brief Get actived window overlap areas
/// @return 
List<DrawArea> GraphicsObject::GetActivedWinOverlapAreas()
{
	List<DrawArea> getAreas;

	for (mainwins.Begin(); !mainwins.IsEnd(); mainwins.Next())
	{
		Window* win = mainwins.Item();

		if (activedwin != win)
		{
			if (layer.IsAreaOverlap(activedwin->GetArea(), win->GetArea()))
			{
				getAreas.Add(layer.GetOverlapArea(activedwin->GetArea(), win->GetArea()));
			}
		}
	}

	return getAreas;
}


/// @brief Cut actived window overlap areas
/// @param areas 
/// @return 
List<DrawArea> GraphicsObject::CutActivedWinOverlapAreas(List<DrawArea> areas)
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
List<DrawArea> GraphicsObject::InciseActivedWinOverlapAreas(List<DrawArea> areas)
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


/// @brief Create main window
/// @return 
Window* GraphicsObject::Create()
{
	Window* win = new Window();
	win->Init(&sysinfo);
	mainwins.Add(win);
	return win;
}


/// @brief Destory main window
/// @param mainwin 
/// @return 
bool GraphicsObject::Destroy(Window* win)
{
	if (NULL != win)
	{
		mainwins.Remove(win);
		delete win;
		return true;
	}
	return false;
}
