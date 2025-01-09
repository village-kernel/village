//###########################################################################
// vg_mainwins.cpp
// Definitions of the functions that manage mainwins
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_mainwins.h"
#include "vk_event_codes.h"


/// @brief Constructor
VgMainWins::VgMainWins(VgDevices& devices)
	:devices(devices),
	defWindow(NULL),
	actWindow(NULL),
	curWindow(NULL)
{
}


/// @brief Destructor
VgMainWins::~VgMainWins()
{
}


/// @brief Setup
void VgMainWins::Setup()
{
	//Create an default window
	defWindow = new VgWindow();
	defWindow->SetFixed(true);
	defWindow->Initiate(&devices);

	//Set default window as active window
	actWindow = defWindow;
}


/// @brief Execute
void VgMainWins::Execute()
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
		if (VgWindow::_Middle == actWindow->GetPlace())
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
void VgMainWins::Exit()
{
	windows.Release();
}


/// @brief Create window
/// @return 
VgWindow* VgMainWins::Create()
{
	VgWindow* window = new VgWindow();
	window->Initiate(&devices);
	windows.Add(window);
	actWindow = window;
	return window;
}


/// @brief Destory window
/// @param window 
/// @return 
bool VgMainWins::Destroy(VgWindow* window)
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
bool VgMainWins::IsExist(VgWindow* window)
{
	return windows.IsExist(window);
}


/// @brief Updata input
void VgMainWins::UpdataInput()
{
	static VgInputData last;

	input = devices.indev->Read();

	if (VgIndevType::_Mouse == devices.indev->GetType())
	{
		axis.point.x = input.point.x - last.point.x;
		axis.point.y = input.point.y - last.point.y;
		last = input;
	}
}


/// @brief Update cursor
void VgMainWins::UpdateCursor()
{
	if ((devices.indev->GetType() == VgIndevType::_Mouse) && 
		(devices.indev->Cursor() != NULL))
	{
		curWindow = devices.indev->Cursor();
		RedrawResizeWindowOverlapAreas(curWindow, ResizeMethod::_Move);
	}
}


/// @brief Execute window
void VgMainWins::ExecuteWindow()
{
	VgWindow* window = SelectActWindow();

	if (NULL != window)
	{
		window->Execute(input);
	}
}


/// @brief Update window
void VgMainWins::UpdateWindow()
{
	for (windows.Begin(); !windows.IsEnd(); windows.Next())
	{
		VgWindow* item = windows.Item();
		
		if (item->HasUpdateRequest())
		{
			RedrawWindowUpdateAreas(item);
			item->ClearUpdateRequest();
		}
	}
}


/// @brief Check resize method
/// @param input 
/// @param axis 
/// @return 
VgMainWins::ResizeMethod VgMainWins::CheckResizeMethod(VgPoint input, VgPoint axis)
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
bool VgMainWins::IsActWindowResize(ResizeMethod& resizeMethod)
{
	static bool isResizeMode = false;
	static ResizeMethod staticResizeMethod = ResizeMethod::_None;

	if (actWindow->IsFixed()) return false;

	if (EventCode::_BtnLeft == input.key)
	{
		if (VgKeyState::_Pressed == input.state)
		{
			if (!isResizeMode || staticResizeMethod > ResizeMethod::_Adjust)
			{
				staticResizeMethod = CheckResizeMethod(input.point, axis.point);
				isResizeMode = (ResizeMethod::_None != staticResizeMethod);
			}
			resizeMethod = staticResizeMethod;
		}
		else if (VgKeyState::_Released == input.state)
		{
			isResizeMode = false;
			resizeMethod = ResizeMethod::_None;
		}
	}

	return isResizeMode;
}


/// @brief Selected active window
/// @return 
VgWindow* VgMainWins::SelectActWindow()
{
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		VgWindow* item = windows.Item();

		if (item->IsInLayerArea(input.point.x, input.point.y))
		{
			return item;
		}
	}
	return actWindow;
}


/// @brief Is actived window change
/// @return 
bool VgMainWins::IsActWindowSelect()
{
	static bool isPressed = false;

	if (EventCode::_BtnLeft == input.key)
	{
		if (!isPressed && VgKeyState::_Pressed == input.state)
		{
			isPressed = true;

			VgWindow* selWindow = SelectActWindow();
			
			if (actWindow != selWindow)
			{
				actWindow = selWindow; return true;
			}
		}
		else if (VgKeyState::_Released == input.state)
		{
			isPressed = false;
		}
	}

	return false;
}


/// @brief Get window upper areas
/// @param window 
/// @return 
VgDrawAreas VgMainWins::GetWindowUpperAreas(VgWindow* window)
{
	VgDrawAreas areas;

	if (window != curWindow)
	{
		for (windows.Begin(); !windows.IsEnd(); windows.Next())
		{
			VgWindow* item = windows.Item();

			if (item == window) continue;

			if (window->GetPlace() < item->GetPlace())
			{
				areas.Add(item->GetLayerArea());
			}

			if (item->HasFloatable())
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
VgDrawAreas VgMainWins::RedrawFloatWindowAreas(VgDrawAreas areas, VgWindow* window)
{
	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		VgWindow* item = windows.Item();

		if (item == window) continue;

		if (!item->HasFloatable()) continue;

		areas = item->RedrawFloatAreas(areas);
	}

	return areas;
}


/// @brief Redraw other window overlap areas
/// @param areas 
/// @param window 
/// @param place 
/// @return 
VgDrawAreas VgMainWins::RedrawOtherWindowAreas(VgDrawAreas areas, VgWindow* window, VgWindow::Place place)
{
	VgDrawAreas cutAreas = areas;
	VgDrawAreas mulAreas = areas;

	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		VgWindow* item = windows.Item();

		if (item == window) continue;

		if (place != item->GetPlace()) continue;

		cutAreas = item->RedrawWedgetAreas(cutAreas);

		item->RedrawMultiplyAreas(mulAreas);
	}

	return cutAreas;
}


/// @brief Redraw other window overlap areas
/// @param window 
void VgMainWins::RedrawOtherWindowAreas(VgDrawAreas areas, VgWindow* window)
{
	//Cut window area from redraw areas
	areas = layer.CutAreaFromAreas(areas, curWindow->GetLayerArea());

	//Redraw float windows
	areas = RedrawFloatWindowAreas(areas, window);

	//Redraw top windows
	areas = RedrawOtherWindowAreas(areas, window, VgWindow::_Top);

	//Redraw middle windows
	areas = RedrawOtherWindowAreas(areas, window, VgWindow::_Middle);

	//Redraw bottom windows
	RedrawOtherWindowAreas(areas, window, VgWindow::_Bottom);
}


/// @brief Redraw window self areas
/// @param window 
void VgMainWins::RedrawSelfWindowAreas(VgWindow* window)
{
	//Return when the window area invalid
	if (!window->IsLayerAreaValid()) return;

	//Get upper areas
	VgDrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	VgDrawAreas overlaps; overlaps.Add(window->GetLayerArea());

	//Calc redraw areas
	VgDrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//VgWindow redraw
	window->Redraw(redraws);
}


/// @brief Redraw window update areas
/// @param window 
void VgMainWins::RedrawWindowUpdateAreas(VgWindow* window)
{
	//Get upper areas
	VgDrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	VgDrawAreas overlaps = window->GetUpdateAreas();

	//Calc redraw areas
	VgDrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//Redraw other window areas
	RedrawOtherWindowAreas(overlaps, window);

	//VgWindow redraw
	window->Redraw(redraws);
}


/// @brief Get resize window overlap areas
/// @param window 
/// @return 
VgDrawAreas VgMainWins::GetResizeWindowOverlapAreas(VgWindow* window, ResizeMethod resizeMethod)
{
	VgDrawArea oldArea = window->GetLayerArea();
	
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

	VgDrawArea newArea = window->GetLayerArea();

	return layer.CutOverlapAreas(oldArea, newArea);
}


/// @brief Redraw resize window overlap areas
/// @param window 
void VgMainWins::RedrawResizeWindowOverlapAreas(VgWindow* window, ResizeMethod resizeMethod)
{
	//Get resize overlap areas
	VgDrawAreas areas = GetResizeWindowOverlapAreas(window, resizeMethod);

	//Redraw other window areas
	RedrawOtherWindowAreas(areas, window);

	//Redraw resize window areas
	RedrawSelfWindowAreas(window);
}


/// @brief Resize window execute
/// @param window 
void VgMainWins::ResizeWindowExecute(VgWindow* window, ResizeMethod resizeMethod)
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
void VgMainWins::DestroyCloseWindow(VgWindow* window, ResizeMethod resizeMethod)
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
VgDrawAreas VgMainWins::GetSelWindowOverlapAreas(VgWindow* window)
{
	VgDrawAreas areas;

	for (windows.Begin(); !windows.IsEnd(); windows.Next())
	{ 
		if (windows.Item() == window) break;
	}

	for (windows.Next(); !windows.IsEnd(); windows.Next())
	{
		VgWindow* item = windows.Item();

		if (VgWindow::_Middle != item->GetPlace()) continue;

		areas.Add(item->GetLayerArea());
	}

	return areas;
}


/// @brief Redraw actived window overlap areas
/// @param window 
void VgMainWins::RedrawSelWindowOverlapAreas(VgWindow* window)
{
	//Get upper areas
	VgDrawAreas uppers = GetWindowUpperAreas(window);

	//Get overlap areas
	VgDrawAreas overlaps = GetSelWindowOverlapAreas(window);

	//Calc redraw areas
	VgDrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//VgWindow redraw
	window->Redraw(redraws);
}


/// @brief Swap active window
/// @param window 
void VgMainWins::SwapActWindowListNode(VgWindow* window)
{
	windows.MoveToEnd(window);
}


/// @brief Execute always focus actived window
/// @param window 
void VgMainWins::AlwaysFocusWindowExecute(VgWindow* window)
{
	if (window->IsAlwaysFocus())
	{
		window->Execute(input);
	}
}
