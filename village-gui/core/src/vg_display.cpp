//###########################################################################
// vg_display.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_display.h"


/// @brief Constructor
GraphicsDisplay::GraphicsDisplay(SystemInfo& sysinfo)
	:sysinfo(sysinfo),
	activelcd(NULL),
	isReady(false)
{
}


/// @brief Destructor
GraphicsDisplay::~GraphicsDisplay()
{
}


/// @brief Display setup
void GraphicsDisplay::Setup()
{
	isReady = false;

	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		lcddevs.Item()->Setup();
	}

	isReady = true;
}


/// @brief Display execute
void GraphicsDisplay::Execute()
{
	DrawData draw;

	while (sysinfo.draws.Pop(&draw))
	{
		if (SelectActivedLcddev(draw.area))
		{
			activelcd->Flush(draw.area, draw.pixels);
		}
	}
}


/// @brief Display exit
void GraphicsDisplay::Exit()
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		lcddevs.Item()->Exit();
	}
}


/// @brief Display select actived lcddev
/// @param arae 
bool GraphicsDisplay::SelectActivedLcddev(DrawArea area)
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		Lcddev* lcddev = lcddevs.Item();

		if ((area.x0 <= lcddev->GetWidth()) &&
			(area.y0 <= lcddev->GetHeight()))
		{
			activelcd = lcddev;
			return true;
		}
	}
	return false;
}


/// @brief Display register lcddev
/// @param lcd 
void GraphicsDisplay::RegisterLcddev(Lcddev* lcd)
{
	lcddevs.Add(lcd);
	if (isReady) lcd->Setup();
}


/// @brief Display unregister lcddev
/// @param lcd 
void GraphicsDisplay::UnregisterLcddev(Lcddev* lcd)
{
	if (isReady) lcd->Exit();
	lcddevs.Remove(lcd);
}
