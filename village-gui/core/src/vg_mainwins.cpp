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
	defaultWin(NULL),
	activedWin(NULL),
	selectedWin(NULL),
	cursorWin(NULL)
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
	defaultWin = new VgWindow();
	defaultWin->SetFixed(true);
	defaultWin->Initiate(&devices);

	//Set default window as active window
	activedWin = defaultWin;
	selectedWin = defaultWin;

	//Create cursor window
	cursorWin = new VgCursor();
	cursorWin->Initiate(&devices);
}


/// @brief Execute
void VgMainWins::Execute()
{
	//Update input
	UpdataInput();

	//Update cursor
	UpdateCursor();

	//Update selected
	UpdateSelected();

	//Update actived
	UpdateActived();

	//Update window
	UpdateWindow();
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
	activedWin = window;
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
		input.axis.x = input.point.x - last.point.x;
		input.axis.y = input.point.y - last.point.y;
		last = input;
	}
}


/// @brief Update cursor
void VgMainWins::UpdateCursor()
{
	if (VgIndevType::_Mouse == devices.indev->GetType())
	{
		//Execute cursor window
		cursorWin->Execute(input);

		//Redraw cursor window area
		RedrawResizeWindowOverlapAreas(cursorWin);
	}
}


/// @brief Update selected window
/// @return 
void VgMainWins::UpdateSelected()
{
	//Select window
	if (VgKeyState::_Released == input.state)
	{
		for (windows.End(); !windows.IsBegin(); windows.Prev())
		{
			VgWindow* item = windows.Item();

			if (item->IsInLayerArea(input.point.x, input.point.y))
			{
				selectedWin = item; break;
			}
		}
	}

	//Execute selected window
	selectedWin->Execute(input);
}


/// @brief Is actived window change
/// @return 
bool VgMainWins::IsActivedWinChange()
{
	static bool isPressed = false;

	if (EventCode::_BtnLeft == input.key || EventCode::_BtnRight == input.key)
	{
		if (!isPressed && VgKeyState::_Pressed == input.state)
		{
			isPressed = true; return (activedWin != selectedWin);
		}
		else if (VgKeyState::_Released == input.state)
		{
			isPressed = false;
		}
	}

	return false;
}


/// @brief Update Actived window
void VgMainWins::UpdateActived()
{
	if (IsActivedWinChange())
	{
		activedWin->SetActived(false);
		activedWin = selectedWin;
		activedWin->SetActived(true);

		if (VgWindow::_Middle == activedWin->GetPlace())
		{
			RedrawSelWindowOverlapAreas(activedWin);

			SwapActWindowListNode(activedWin);
		}
	}
}


/// @brief Update window
void VgMainWins::UpdateWindow()
{
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		VgWindow* item = windows.Item();
		
		if (item->HasUpdateRequest())
		{
			RedrawWindowUpdateOverlapAreas(item);

			item->ClearUpdateRequest();
		}

		if (item->IsResizeRequest())
		{
			RedrawResizeWindowOverlapAreas(item);

			DestroyCloseWindow(item);

			item->ClearResizeRequest();
		}
	}
}


/// @brief Get window upper areas
/// @param window 
/// @return 
VgDrawAreas VgMainWins::GetWindowUpperAreas(VgWindow* window)
{
	VgDrawAreas areas;

	if (window != cursorWin)
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

		areas.Add(cursorWin->GetLayerArea());
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

	//Redraw other window areas
	for (windows.End(); !windows.IsBegin(); windows.Prev())
	{
		VgWindow* item = windows.Item();

		if (item == window) continue;

		if (place != item->GetPlace()) continue;

		cutAreas = item->RedrawWedgetAreas(cutAreas);
	}

	return cutAreas;
}


/// @brief Redraw other window overlap areas
/// @param window 
void VgMainWins::RedrawOtherWindowAreas(VgDrawAreas overlaps, VgWindow* window)
{
	//Cut cursor area from redraw areas
	overlaps = layer.CutAreaFromAreas(overlaps, cursorWin->GetLayerArea());

	//Redraw float windows
	overlaps = RedrawFloatWindowAreas(overlaps, window);

	//Redraw top windows
	overlaps = RedrawOtherWindowAreas(overlaps, window, VgWindow::_Top);

	//Redraw middle windows
	overlaps = RedrawOtherWindowAreas(overlaps, window, VgWindow::_Middle);

	//Redraw bottom windows
	RedrawOtherWindowAreas(overlaps, window, VgWindow::_Bottom);
}


/// @brief Redraw window self areas
/// @param window 
void VgMainWins::RedrawSelfWindowAreas(VgDrawAreas overlaps, VgWindow* window)
{
	//Return when the window area invalid
	if (!window->IsLayerAreaValid()) return;

	//Get upper areas
	VgDrawAreas uppers = GetWindowUpperAreas(window);

	//Calc redraw areas
	VgDrawAreas redraws = layer.CalcOverlapAreas(window->GetLayerArea(), overlaps, uppers);

	//VgWindow redraw
	window->Redraw(redraws);
}


/// @brief Redraw window update areas
/// @param window 
void VgMainWins::RedrawWindowUpdateOverlapAreas(VgWindow* window)
{
	//Get other window update areas
	VgDrawAreas areas = window->GetUpdateAreas();

	//Redraw other window areas
	RedrawOtherWindowAreas(areas, window);

	//Redraw self window areas
	RedrawSelfWindowAreas(areas, window);
}


/// @brief Redraw resize window overlap areas
/// @param window 
void VgMainWins::RedrawResizeWindowOverlapAreas(VgWindow* window)
{
	//Get resize window areas
	VgUpdateAreas resizeAreas = window->GetResizeAreas();

	//Redraw other window areas
	RedrawOtherWindowAreas(resizeAreas.oldAreas, window);

	//Redraw resize window areas
	RedrawSelfWindowAreas(resizeAreas.newAreas, window);
}


/// @brief Destory close window
/// @param window 
void VgMainWins::DestroyCloseWindow(VgWindow* window)
{
	if (window->IsCloseRequest())
	{
		activedWin = defaultWin;
		selectedWin = defaultWin;
		Destroy(window);
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
	//Get overlap areas
	VgDrawAreas areas = GetSelWindowOverlapAreas(window);

	//Redraw self window areas
	RedrawSelfWindowAreas(areas, window);
}


/// @brief Swap active window
/// @param window 
void VgMainWins::SwapActWindowListNode(VgWindow* window)
{
	windows.MoveToEnd(window);
}
