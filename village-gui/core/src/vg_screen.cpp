//###########################################################################
// vg_screen.cpp
// Definitions of the functions that manage screen
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_screen.h"


/// @brief Constructor
VgScreen::VgScreen(VgDevices& devices)
	:devices(devices),
	isReady(false)
{
}


/// @brief Destructor
VgScreen::~VgScreen()
{
}


/// @brief Display setup
void VgScreen::Setup()
{
	isReady = false;

	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		lcddevs.Item()->Setup(&devices);
	}

	devices.lcddev = lcddevs.Begin();

	isReady = true;
}


/// @brief Display execute
void VgScreen::Execute()
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
void VgScreen::Exit()
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		lcddevs.Item()->Exit();
	}
}


/// @brief Display register lcddev
/// @param lcd 
void VgScreen::RegisterLcddev(Lcddev* lcd)
{
	lcddevs.Add(lcd);
	if (isReady) lcd->Setup(&devices);
}


/// @brief Display unregister lcddev
/// @param lcd 
void VgScreen::UnregisterLcddev(Lcddev* lcd)
{
	if (isReady) lcd->Exit();
	lcddevs.Remove(lcd);
}
