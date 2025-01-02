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

	//Update cursor
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
		ExecuteWindow();

		UpdateWindow();
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


/// @brief Is window exist
/// @param win 
/// @return 
bool VgGroup::IsExist(Window* window)
{
	if (NULL != window)
	{
		for (windows.Begin(); !windows.IsEnd(); windows.Next())
		{
			if (window == windows.Item()) return true;
		}
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


/// @brief Execute window
void VgGroup::ExecuteWindow()
{
	Window* window = SelectActWindow();

	if (NULL != window)
	{
		window->Execute(input);
	}
}


/// @brief Update window
void VgGroup::UpdateWindow()
{
	for (windows.Begin(); !windows.IsEnd(); windows.Next())
	{
		Window* item = windows.Item();
		
		if (item->IsUpdateRequest())
		{
			RedrawWindowUpdateAreas(item);
			item->UpdateRequest(false);
		}
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

	if (EventCode::_BtnLeft == input.key)
	{
		if (KeyState::_Pressed == input.state)
		{
			if (!isResizeMode || staticResizeMethod > ResizeMethod::_Adjust)
			{
				staticResizeMethod = CheckResizeMethod(input.point, axis.point);
				isResizeMode = (ResizeMethod::_None != staticResizeMethod);
			}
			resizeMethod = staticResizeMethod;
		}
		else if (KeyState::_Released == input.state)
		{
			isResizeMode = false;
			resizeMethod = ResizeMethod::_None;
		}
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

		if (item->IsInArea(input.point.x, input.point.y))
		{
			return item;
		}
	}
	return actWindow;
}


/// @brief Is actived window change
/// @return 
bool VgGroup::IsActWindowSelect()
{
	static bool isPressed = false;

	if (EventCode::_BtnLeft == input.key)
	{
		if (!isPressed && KeyState::_Pressed == input.state)
		{
			isPressed = true;

			Window* selWindow = SelectActWindow();
			
			if (actWindow != selWindow)
			{
				actWindow = selWindow; return true;
			}
		}
		else if (KeyState::_Released == input.state)
		{
			isPressed = false;
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

			if (item == window) continue;

			if (window->GetPlace() < item->GetPlace())
			{
				areas.Add(item->GetLayerArea());
			}

			if (item->IsFloatable())
			{
				areas.Append(item->GetFloatAreas());
			}
		}

		areas = layer.CutAreasFromAreas(areas, window->GetFloatAreas());

		areas.Add(curWindow->GetLayerArea());
	}

	return areas;
}


/// @brief Redraw Float window overlap areas
/// @param areas 
/// @param window 
/// @param place 
/// @return 
DrawAreas VgGroup::RedrawFloatWindowAreas(DrawAreas areas, Window* window)
{
	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		Window* item = windows.Item();

		if (item == window) continue;

		if (!item->IsFloatable()) continue;

		areas = item->RedrawFloatAreas(areas);
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

		areas = item->RedrawWedgetAreas(areas);
	}

	return areas;
}


/// @brief Redraw other window overlap areas
/// @param window 
void VgGroup::RedrawOtherWindowAreas(DrawAreas areas, Window* window)
{
	//Cut window area from redraw areas
	areas = layer.CutAreaFromAreas(areas, curWindow->GetLayerArea());

	//Redraw float windows
	areas = RedrawFloatWindowAreas(areas, window);

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
	//Return when the window area invalid
	if (!window->IsAreaValid()) return;

	//Get upper areas
	DrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	DrawAreas overlaps; overlaps.Add(window->GetLayerArea());

	//Calc redraw areas
	DrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//Window redraw
	window->Redraw(redraws);
}


/// @brief Redraw window update areas
/// @param window 
void VgGroup::RedrawWindowUpdateAreas(Window* window)
{
	//Get upper areas
	DrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	DrawAreas overlaps = window->GetUpdateAreas();

	//Calc redraw areas
	DrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//Redraw other window areas
	RedrawOtherWindowAreas(overlaps, window);

	//Window redraw
	window->Redraw(redraws);
}


/// @brief Get resize window overlap areas
/// @param window 
/// @return 
DrawAreas VgGroup::GetResizeWindowOverlapAreas(Window* window, ResizeMethod resizeMethod)
{
	DrawArea oldArea = window->GetLayerArea();
	
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

	DrawArea newArea = window->GetLayerArea();

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

		actWindow = windows.End();
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

		areas.Add(item->GetLayerArea());
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
	DrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

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
