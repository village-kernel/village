//###########################################################################
// vg_group.cpp
// Definitions of the functions that manage group
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_group.h"


/// @brief Constructor
GraphicsGroup::GraphicsGroup(GraphicsData& databus)
	:databus(databus)
{
}


/// @brief Destructor
GraphicsGroup::~GraphicsGroup()
{
}


/// @brief Setup
void GraphicsGroup::Setup()
{
	
}


/// @brief Execute
void GraphicsGroup::Execute()
{
	static IndevData input;

	//if (input != databus->input)
	{
		input = databus.input;

		if (!activedwin->IsCanSelecte(input.point.x, input.point.y))
		{
			for (mainwins.Begin(); !mainwins.IsEnd(); mainwins.Next())
			{
				Window* win = mainwins.Item();

				if (win->IsCanSelecte(input.point.x, input.point.y))
				{
					activedwin = win;
					break;
				}
			}
		}

		//activedwin->Execute(input);
	}
}


/// @brief Exit
void GraphicsGroup::Exit()
{
	mainwins.Release();
}


/// @brief Create main window
/// @return 
Window* GraphicsGroup::Create()
{
	Window* win = new Window();
	mainwins.Add(win);
	return win;
}


/// @brief Destory main window
/// @param mainwin 
/// @return 
bool GraphicsGroup::Destroy(Window* win)
{
	if (NULL != win)
	{
		mainwins.Remove(win);
		delete win;
		return true;
	}
	return false;
}
