//###########################################################################
// vg_displays.cpp
// Definitions of the functions that manage displays
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_displays.h"


/// @brief Constructor
VgDisplays::VgDisplays(VgDevices& devices)
	:devices(devices),
	isReady(false)
{
}


/// @brief Destructor
VgDisplays::~VgDisplays()
{
}


/// @brief Display setup
void VgDisplays::Setup()
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
void VgDisplays::Execute()
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		VgLcddev* lcddev = lcddevs.Item();

		if (VgIndevType::_Mouse == devices.indev->GetType())
		{
			VgInputData input = devices.indev->Read();

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
void VgDisplays::Exit()
{
	for (lcddevs.Begin(); !lcddevs.IsEnd(); lcddevs.Next())
	{
		lcddevs.Item()->Exit();
	}
}


/// @brief Display register lcddev
/// @param lcd 
void VgDisplays::RegisterLcddev(VgLcddev* lcd)
{
	lcddevs.Add(lcd);
	if (isReady) lcd->Setup(&devices);
}


/// @brief Display unregister lcddev
/// @param lcd 
void VgDisplays::UnregisterLcddev(VgLcddev* lcd)
{
	if (isReady) lcd->Exit();
	lcddevs.Remove(lcd);
}
