//###########################################################################
// vg_input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_input.h"


/// @brief Constructor
GraphicsInput::GraphicsInput(SystemInfo& sysinfo)
	:sysinfo(sysinfo),
	isReady(false)
{
}


/// @brief Destructor
GraphicsInput::~GraphicsInput()
{
}


/// @brief Input setup
void GraphicsInput::Setup()
{
	isReady = false;

	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		indevs.Item()->Setup();
	}

	isReady = true;
}


/// @brief Input execute
void GraphicsInput::Execute()
{
	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		Indev* indev = indevs.Item();
		
		sysinfo.input = indev->Read();
	}
}


/// @brief Input exit
void GraphicsInput::Exit()
{
	for (indevs.Begin(); !indevs.IsEnd(); indevs.Next())
	{
		indevs.Item()->Exit();
	}
}


/// @brief Input register indev
/// @param indev 
void GraphicsInput::RegisterIndev(Indev* indev)
{
	indevs.Add(indev);
	if (isReady) indev->Setup();
}


/// @brief Input unregister indev
/// @param indev 
void GraphicsInput::UnregisterIndev(Indev* indev)
{
	if (isReady) indev->Exit();
	indevs.Remove(indev);
}
