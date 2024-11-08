//###########################################################################
// vg_group.cpp
// Definitions of the functions that manage group
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_group.h"
#include "vk_event_codes.h"


/// @brief Constructor
GraphicsGroup::GraphicsGroup(GraphicsData& data)
	:data(data)
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

	while (data.input.Pop(&input))
	{
		//Select activedwin
		SelectWindow(input);

		//activedwin->Execute(input);
	}
}


/// @brief Exit
void GraphicsGroup::Exit()
{
	mainwins.Release();
}


/// @brief Select Window
/// @param input 
void GraphicsGroup::SelectWindow(IndevData& input)
{
	if (EventCode::_BtnLeft == input.key && KeyState::_Pressed == input.state)
	{
		if (!activedwin->IsCanSelecte(input.point.x, input.point.y))
		{
			for (mainwins.Begin(); !mainwins.IsEnd(); mainwins.Next())
			{
				Window* win = mainwins.Item();

				if (win->IsCanSelecte(input.point.x, input.point.y))
				{
					activedwin = win;
					return;
				}
			}
		}
	}
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
