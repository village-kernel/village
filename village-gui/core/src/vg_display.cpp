//###########################################################################
// vg_display.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_display.h"


/// @brief Constructor
GraphicsDisplay::GraphicsDisplay(GraphicsDevices& devices)
	:devices(devices),
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

	devices.lcddev = lcddevs.Begin();

	isReady = true;
}


/// @brief Display execute
void GraphicsDisplay::Execute()
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		Lcddev* lcddev = lcddevs.Item();

		if (IndevType::_Mouse == devices.indev->GetType())
		{
			IndevData input = devices.indev->Read();

			if ((input.point.x <= lcddev->GetWidth()) &&
				(input.point.y <= lcddev->GetHeight()))
			{
				devices.lcddev = lcddev;
				break;
			}
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
