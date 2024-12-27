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
	defWindow->Initiate(&devices);

	//Set default window as active window
	actWindow = defWindow;
}


/// @brief Execute
void VgGroup::Execute()
{
	//Update input
	UpdataInput();

	//Update mouse cursor
	UpdateCursor();

	//Resize actived window
	ResizeMethod resizeMethod = ResizeMethod::_None;
	
	if (IsActWindowResize(resizeMethod))
	{
		ResizeWindowExecute(actWindow, resizeMethod);

		RedrawResizeWindowOverlapAreas(actWindow, resizeMethod);

		DestroyCloseWindow(actWindow, resizeMethod);
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
	actWindow = window;
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


/// @brief Update cursor
void VgGroup::UpdateCursor()
{
	if ((devices.indev->GetType() == IndevType::_Mouse) && 
		(devices.indev->Cursor() != NULL))
	{
		curWindow = devices.indev->Cursor();
		RedrawResizeWindowOverlapAreas(curWindow, ResizeMethod::_Move);
	}
}


/// @brief Check resize method
/// @param input 
/// @param axis 
/// @return 
VgGroup::ResizeMethod VgGroup::CheckResizeMethod(Point input, Point axis)
{
	ResizeMethod resizeMethod = ResizeMethod::_None;

	if (axis.x || axis.y)
	{
		if (actWindow->IsInMoveArea(input.x, input.y))
			resizeMethod = ResizeMethod::_Move;
		if (actWindow->IsInResizeArea(input.x, input.y))
			resizeMethod = ResizeMethod::_Adjust;
	}
	else
	{
		if (actWindow->IsInMaximizeArea(input.x, input.y))
			resizeMethod = ResizeMethod::_Maximize;
		if (actWindow->IsInMinimizeArea(input.x, input.y))
			resizeMethod = ResizeMethod::_Minimize;
		if (actWindow->IsInCloseArea(input.x, input.y))
			resizeMethod = ResizeMethod::_Close;
	}

	return resizeMethod;
}


/// @brief Is actived window resize
/// @return 
bool VgGroup::IsActWindowResize(ResizeMethod& resizeMethod)
{
	static bool isResizeMode = false;
	static ResizeMethod staticResizeMethod = ResizeMethod::_None;

	if (actWindow->IsFixed()) return false;

	if ((EventCode::_BtnLeft == input.key) && (KeyState::_Pressed == input.state))
	{
		if (!isResizeMode)
		{
			staticResizeMethod = CheckResizeMethod(input.point, axis.point);
			isResizeMode = (ResizeMethod::_None != staticResizeMethod);
		}
		resizeMethod = staticResizeMethod;
	}
	else
	{
		isResizeMode = false;
		resizeMethod = ResizeMethod::_None;
	}

	return isResizeMode;
}


/// @brief Selected active window
/// @return 
Window* VgGroup::SelectActWindow()
{
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		Window* item = windows.Item();

		if (layer.IsCoordinateInArea(input.point.x, input.point.y, item->GetArea()))
		{
			return item;
		}
	}
	return NULL;
}


/// @brief Is actived window change
/// @return 
bool VgGroup::IsActWindowSelect()
{
	if ((EventCode::_BtnLeft == input.key) && (KeyState::_Pressed == input.state))
	{
		Window* window = SelectActWindow();

		if ((NULL != window) && (actWindow != window))
		{
			actWindow = window; return true;
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

			if (window->GetPlace() < item->GetPlace())
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
	//Cut cursor area from redraw areas
	areas = layer.CutAreaFromAreas(areas, curWindow->GetArea());

	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		Window* item = windows.Item();

		if (item == window) continue;

		if (place != item->GetPlace()) continue;

		areas = item->RedrawWedgetAreas(item, areas);
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


/// @brief Get resize window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetResizeWindowOverlapAreas(Window* window, ResizeMethod resizeMethod)
{
	DrawArea oldArea = window->GetArea();
	
	switch (resizeMethod)
	{
		case ResizeMethod::_Move:
			window->AxisMove(axis.point.x, axis.point.y);
			break;
		case ResizeMethod::_Adjust:
			window->Adjust(axis.point.x, axis.point.y);
			break;
		case ResizeMethod::_Maximize:
			window->Maximize();
			break;
		case ResizeMethod::_Minimize:
			window->Minimize();
			break;
		case ResizeMethod::_Close:
			window->Close();
			break;
		default:
			break;
	}

	DrawArea newArea = window->GetArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw resize window overlap areas
/// @param window 
void VgGroup::RedrawResizeWindowOverlapAreas(Window* window, ResizeMethod resizeMethod)
{
	//Get resize overlap areas
	DrawAreas areas = GetResizeWindowOverlapAreas(window, resizeMethod);

	//Redraw other window areas
	RedrawOtherWindowAreas(areas, window);

	//Redraw resize window areas
	RedrawSelfWindowAreas(window);
}


/// @brief Resize window execute
/// @param window 
void VgGroup::ResizeWindowExecute(Window* window, ResizeMethod resizeMethod)
{
	if ((ResizeMethod::_Maximize == resizeMethod) ||
		(ResizeMethod::_Minimize == resizeMethod) ||
		(ResizeMethod::_Close    == resizeMethod))
	{
		window->Execute(input);
	}
}


/// @brief Destory close window
/// @param window 
void VgGroup::DestroyCloseWindow(Window* window, ResizeMethod resizeMethod)
{
	if (ResizeMethod::_Close == resizeMethod)
	{
		Destroy(window);

		actWindow = defWindow;
	}
}


/// @brief Get selected window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetSelWindowOverlapAreas(Window* window)
{
	DrawAreas areas;

	for (windows.Begin(); !windows.IsEnd(); windows.Next())
	{ 
		if (windows.Item() == window) break;
	}

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
