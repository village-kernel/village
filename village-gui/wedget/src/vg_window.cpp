//###########################################################################
// vg_window.cpp
// Definitions of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_window.h"


/// @brief Constructor
VgWindow::VgWindow()
	:focus(false),
	place(_Middle),
	resizeSide(0)
{
	SetTitle((char*)"window");
}


/// @brief Destructor
VgWindow::~VgWindow()
{
}


/// @brief Get navbar
/// @return 
VgNavbar* VgWindow::GetNavbar()
{
	return &navbar;
}


/// @brief Is in move area
/// @param x 
/// @param y 
/// @return 
bool VgWindow::IsInMoveArea(int x, int y)
{
	if (!navbar.IsHidden() && navbar.IsEnable())
	{
		return navbar.IsInLayerArea(x, y);
	}
	return layer.IsCoordinateInArea(x, y, layerArea);
}


/// @brief Is in resize area
/// @param x 
/// @param y 
/// @return 
bool VgWindow::IsInResizeArea(int x, int y)
{
	resizeSide = 0;

	if ((math.IsInRange(x, layerArea.sx - resize_range, layerArea.ex + resize_range)) &&
		(math.IsInRange(y, layerArea.sy - resize_range, layerArea.ey + resize_range)))
	{
		if (math.IsInRange(x - layerArea.sx, -resize_range, resize_range))
			resizeSide |= ResizeSide::_LeftSide;
		if (math.IsInRange(layerArea.ex - x, -resize_range, resize_range))
			resizeSide |= ResizeSide::_RightSide;
		if (math.IsInRange(y - layerArea.sy, -resize_range, resize_range))
			resizeSide |= ResizeSide::_UpSide;
		if (math.IsInRange(layerArea.ey - y, -resize_range, resize_range))
			resizeSide |= ResizeSide::_DownSide;
	}

	return (0 != resizeSide);
}


/// @brief Is in maximize area
/// @param x 
/// @param y 
/// @return 
bool VgWindow::IsInMaximizeArea(int x, int y)
{
	if (!navbar.IsHidden() && navbar.IsEnable())
	{
		return navbar.IsInMaximizeArea(x, y);
	}
	return false;
}


/// @brief Is in minimize area
/// @param x 
/// @param y 
/// @return 
bool VgWindow::IsInMinimizeArea(int x, int y)
{
	if (!navbar.IsHidden() && navbar.IsEnable())
	{
		return navbar.IsInMinimizeArea(x, y);
	}
	return false;
}


/// @brief Is in close area
/// @param x 
/// @param y 
/// @return 
bool VgWindow::IsInCloseArea(int x, int y)
{
	if (!navbar.IsHidden() && navbar.IsEnable())
	{
		return navbar.IsInCloseArea(x, y);
	}
	return false;
}


/// @brief VgWindow set size
/// @param width 
/// @param height 
void VgWindow::SetSize(int width, int height)
{
	VgWedget::SetSize(width, height);

	navbar.SetSize(GetWidth(), navbar_height);
}


/// @brief VgWindow adjust size
/// @param axisx 
/// @param axisy 
void VgWindow::Adjust(int axisx, int axisy)
{
	if (resizeSide & ResizeSide::_LeftSide)
		layerArea.sx += axisx;
	if (resizeSide & ResizeSide::_RightSide)
		layerArea.ex += axisx;
	if (resizeSide & ResizeSide::_UpSide)
		layerArea.sy += axisy;
	if (resizeSide & ResizeSide::_DownSide)
		layerArea.ey += axisy;
	
	navbar.SetSize(GetWidth(), navbar_height);
	navbar.MoveTo(GetX(), GetY());
}


/// @brief VgWindow show on center
void VgWindow::ShowOnCenter()
{
	int x = (devices->lcddev->GetWidth() - GetWidth()) >> 1;
	int y = (devices->lcddev->GetHeight() - GetHeight()) >> 1;
	if (navbar.IsEnable()) y -= navbar_height;
	MoveTo(x, y);
}


/// @brief VgWindow maximize
void VgWindow::Maximize()
{
	static VgDrawArea oldArea;
	static bool isMaximize = false;
	
	if (false == isMaximize)
	{
		oldArea = layerArea;
		MoveTo(0, 0);
		SetSize(devices->lcddev->GetWidth(), devices->lcddev->GetHeight());
		isMaximize = true;
	}
	else
	{
		MoveTo(oldArea.sx, oldArea.sy);
		SetSize(oldArea.ex - oldArea.sx + 1, oldArea.ey - oldArea.sy + 1);
		isMaximize = false;
	}
}


/// @brief VgWindow minimize
void VgWindow::Minimize()
{
	MoveTo(0, 0);
	SetSize(0, 0);
}


/// @brief VgWindow close
void VgWindow::Close()
{
	MoveTo(0, 0);
	SetSize(0, 0);
}


/// @brief Set enable navbar
/// @param enable 
void VgWindow::SetEnableNavbar(bool enable)
{
	navbar.SetEnable(enable);
}


/// @brief Is enable navbar
/// @return 
bool VgWindow::IsEnableNavbar()
{
	return navbar.IsEnable();
}


/// @brief Set hidden navbar
/// @param hidden 
void VgWindow::SetHiddenNavbar(bool hidden)
{
	navbar.SetHidden(hidden);
}


/// @brief Is hidden navbar
/// @return 
bool VgWindow::IsHiddenNavbar()
{
	return navbar.IsHidden();
}


/// @brief Set always focus
/// @param focus 
void VgWindow::SetAlwaysFocus(bool focus)
{
	this->focus = focus;
}


/// @brief Is always focus
/// @return 
bool VgWindow::IsAlwaysFocus()
{
	return focus;
}


/// @brief VgWindow set place
/// @param place 
void VgWindow::SetPlace(Place place)
{
	this->place = place;
}


/// @brief VgWindow get place
/// @return 
VgWindow::Place VgWindow::GetPlace()
{
	return place;
}


/// @brief VgWindow Initiate
/// @param devices 
void VgWindow::InitContent(VgDevices* devices)
{
	AddWedget(&navbar);
}


/// @brief VgWindow Execute
/// @param input 
void VgWindow::ExecContent(VgInputData input)
{

}


/// @brief VgWindow draw
/// @param drawArea 
void VgWindow::DrawContent(VgDrawArea drawArea)
{

}
