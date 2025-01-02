//###########################################################################
// vg_indevs.cpp
// Definitions of the functions that manage indevs
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_indevs.h"


/// @brief Constructor
VgIndevs::VgIndevs(VgDevices& devices)
	:devices(devices),
	isReady(false)
{
}


/// @brief Destructor
VgIndevs::~VgIndevs()
{
}


/// @brief Input setup
void VgIndevs::Setup()
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
void VgIndevs::Execute()
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
void VgIndevs::Exit()
{
	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		indevs.Item()->Exit();
	}
}


/// @brief Input register indev
/// @param indev 
void VgIndevs::RegisterIndev(Indev* indev)
{
	indevs.Add(indev);
	if (isReady) indev->Setup(&devices);
}


/// @brief Input unregister indev
/// @param indev 
void VgIndevs::UnregisterIndev(Indev* indev)
{
	if (isReady) indev->Exit();
	indevs.Remove(indev);
}
