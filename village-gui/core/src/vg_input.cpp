//###########################################################################
// vg_input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_input.h"


/// @brief Constructor
VgInput::VgInput(VgDevices& devices)
	:devices(devices),
	isReady(false)
{
}


/// @brief Destructor
VgInput::~VgInput()
{
}


/// @brief Input setup
void VgInput::Setup()
{
	isReady = false;

	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		indevs.Item()->Setup(&devices);
	}

	devices.indev = indevs.Begin();

	isReady = true;
}


/// @brief Input execute
void VgInput::Execute()
{
	while (1)
	{
		indevs.Next(); if (indevs.IsEnd()) indevs.Begin();

		if (indevs.Item()->IsReady())
		{
			devices.indev = indevs.Item();
			
			indevs.Item()->ClearReady();

			break;
		}
	}
}


/// @brief Input exit
void VgInput::Exit()
{
	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		indevs.Item()->Exit();
	}
}


/// @brief Input register indev
/// @param indev 
void VgInput::RegisterIndev(Indev* indev)
{
	indevs.Add(indev);
	if (isReady) indev->Setup(&devices);
}


/// @brief Input unregister indev
/// @param indev 
void VgInput::UnregisterIndev(Indev* indev)
{
	if (isReady) indev->Exit();
	indevs.Remove(indev);
}
