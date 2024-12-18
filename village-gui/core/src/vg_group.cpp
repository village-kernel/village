//###########################################################################
// vg_group.cpp
// Definitions of the functions that manage group
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_group.h"
#include "vk_event_codes.h"


/// @brief Constructor
VgGroup::VgGroup(VgDevices& devices)
	:devices(devices),
	defWindow(NULL),
	actWindow(NULL),
	curWindow(NULL)
{
}


/// @brief Destructor
VgGroup::~VgGroup()
{
}


/// @brief Setup
void VgGroup::Setup()
{
	//Create an default window
	defWindow = new Window();

	//Set default window as active window
	actWindow = defWindow;
}


/// @brief Execute
void VgGroup::Execute()
{
	//Update input
	UpdataInput();

	//Update mouse cursor
	if (IsCurWindowMove())
	{
		curWindow = devices.indev->Cursor();

		RedrawMoveWindowOverlapAreas(curWindow);
	}

	//Move actived window
	if (IsActWindowMove())
	{
		RedrawMoveWindowOverlapAreas(actWindow);
	}
	//Resize actived window
	else if (IsActWindowResize())
	{
		RedrawResizeWindowOverlapAreas(actWindow);
	}
	//Select actived window
	else if (IsActWindowSelect())
	{
		if (Window::_Middle == actWindow->GetPlace())
		{
			RedrawSelWindowOverlapAreas(actWindow);

			SwapActWindowListNode(actWindow);
		}

		AlwaysFocusWindowExecute(actWindow);
	}
	//Active window execute
	else
	{
		actWindow->Execute(input);
	}
}


/// @brief Exit
void VgGroup::Exit()
{
	windows.Release();
}


/// @brief Create window
/// @return 
Window* VgGroup::Create()
{
	Window* window = new Window();
	window->Initiate(&devices);
	windows.Add(window);
	return window;
}


/// @brief Destory window
/// @param window 
/// @return 
bool VgGroup::Destroy(Window* window)
{
	if (NULL != window)
	{
		windows.Remove(window);
		delete window;
		return true;
	}
	return false;
}


/// @brief Updata input
void VgGroup::UpdataInput()
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


/// @brief Is cursor window move
/// @return 
bool VgGroup::IsCurWindowMove()
{
	if (IndevType::_Mouse != devices.indev->GetType())
		return false;
	if (NULL == devices.indev->Cursor())
		return false;
	return true;
}


/// @brief Is actived window move
/// @return 
bool VgGroup::IsActWindowMove()
{
	if (actWindow->IsFixed()) return false;

	if (EventCode::_BtnLeft != input.key) return false;

	if (KeyState::_Pressed != input.state) return false;

	if (actWindow->IsInMoveArea(input.point.x, input.point.y))
	{
		return (axis.point.x || axis.point.y);
	}

	return false;
}


/// @brief Is actived window resize
/// @return 
bool VgGroup::IsActWindowResize()
{
	if (actWindow->IsFixed()) return false;

	if (EventCode::_BtnLeft != input.key) return false;

	if (KeyState::_Pressed != input.state) return false;

	if (actWindow->IsInResizeArea(input.point.x, input.point.y))
	{
		return (axis.point.x || axis.point.y);
	}

	return false;
}


/// @brief Is actived window change
/// @return 
bool VgGroup::IsActWindowSelect()
{
	if (EventCode::_BtnLeft != input.key) return false;
	
	if (KeyState::_Pressed != input.state) return false;
	
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		Window* item = windows.Item();

		if (layer.IsCoordinateInArea(input.point.x, input.point.y, item->GetArea()))
		{
			if (actWindow != item)
			{
				actWindow = item;
				return true;
			}
			break;
		}
	}
	
	return false;
}


/// @brief Get window upper areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetWindowUpperAreas(Window* window)
{
	DrawAreas areas;

	if (window != curWindow)
	{
		for (windows.Begin(); !windows.IsEnd(); windows.Next())
		{
			Window* item = windows.Item();

			if (Window::_Top == item->GetPlace())
			{
				areas.Add(item->GetArea());
			}	
		}

		areas.Add(curWindow->GetArea());
	}

	return areas;
}


/// @brief Redraw other window overlap areas
/// @param areas 
/// @param window 
/// @param place 
/// @return 
DrawAreas VgGroup::RedrawOtherWindowAreas(DrawAreas areas, Window* window, Window::Place place)
{
	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		Window* item = windows.Item();

		if (item == window) continue;

		if (place != item->GetPlace()) continue;

		DrawAreas cutAreas = areas;

		for (areas.Begin(); !areas.IsEnd(); areas.Next())
		{
			DrawArea area = areas.Item();

			if (layer.IsAreaOverlap(area, item->GetArea()))
			{
				DrawArea redraw = layer.GetOverlapArea(area, item->GetArea());

				item->Redraw(redraw);

				cutAreas = layer.CutAreaFromAreas(cutAreas, redraw);
			}
		}

		areas = cutAreas;
	}

	return areas;
}


/// @brief Redraw other window overlap areas
/// @param window 
void VgGroup::RedrawOtherWindowAreas(DrawAreas areas, Window* window)
{
	//Redraw top windows
	areas = RedrawOtherWindowAreas(areas, window, Window::_Top);

	//Redraw middle windows
	areas = RedrawOtherWindowAreas(areas, window, Window::_Middle);

	//Redraw bottom windows
	RedrawOtherWindowAreas(areas, window, Window::_Bottom);
}


/// @brief Redraw window self areas
/// @param window 
void VgGroup::RedrawSelfWindowAreas(Window* window)
{
	//Get upper areas
	DrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	DrawAreas overlaps; overlaps.Add(window->GetArea());

	//Calc redraw areas
	DrawAreas redraws = layer.CalcOverlapAreas(window->GetArea(), overlaps, uppers);

	//Window redraw
	window->Redraw(redraws);
}


/// @brief Get moved window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetMoveWindowOverlapAreas(Window* window)
{
	DrawArea oldArea = window->GetArea();
	
	window->Move(axis.point.x, axis.point.y);
	
	DrawArea newArea = window->GetArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw move window overlap areas
/// @param window 
void VgGroup::RedrawMoveWindowOverlapAreas(Window* window)
{
	//Get move overlap areas
	DrawAreas areas = GetMoveWindowOverlapAreas(window);

	//Redraw other window areas
	RedrawOtherWindowAreas(areas, window);

	//Redraw move window areas
	RedrawSelfWindowAreas(window);
}


/// @brief Get resize window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetResizeWindowOverlapAreas(Window* window)
{
	DrawArea oldArea = window->GetArea();
	
	window->Resize(input, axis);

	DrawArea newArea = window->GetArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw resize window overlap areas
/// @param window 
void VgGroup::RedrawResizeWindowOverlapAreas(Window* window)
{
	//Get resize overlap areas
	DrawAreas areas = GetResizeWindowOverlapAreas(window);

	//Redraw other window areas
	RedrawOtherWindowAreas(areas, window);

	//Redraw resize window areas
	RedrawSelfWindowAreas(window);
}


/// @brief Get selected window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetSelWindowOverlapAreas(Window* window)
{
	DrawAreas areas;

	windows.Begin(); while(windows.Item() != window) { windows.Next(); }

	for (windows.Next(); !windows.IsEnd(); windows.Next())
	{
		Window* item = windows.Item();

		if (Window::_Middle != item->GetPlace()) continue;

		areas.Add(item->GetArea());
	}

	return areas;
}


/// @brief Redraw actived window overlap areas
/// @param window 
void VgGroup::RedrawSelWindowOverlapAreas(Window* window)
{
	//Get upper areas
	DrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	DrawAreas overlaps = GetSelWindowOverlapAreas(window);

	//Calc redraw areas
	DrawAreas redraws = layer.CalcOverlapAreas(window->GetArea(), overlaps, uppers);

	//Window redraw
	window->Redraw(redraws);
}


/// @brief Swap active window
/// @param window 
void VgGroup::SwapActWindowListNode(Window* window)
{
	windows.Remove(window);
	windows.Add(window);
}


/// @brief Execute always focus actived window
/// @param window 
void VgGroup::AlwaysFocusWindowExecute(Window* window)
{
	if (window->IsAlwaysFocus())
	{
		window->Execute(input);
	}
}
