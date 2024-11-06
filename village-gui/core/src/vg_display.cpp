//###########################################################################
// vg_display.cpp
// Definitions of the functions that manage display
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_display.h"


/// @brief Constructor
GraphicsDisplay::GraphicsDisplay(GraphicsData& databus)
	:databus(databus),
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
	List<DrawData*> draws = databus.draws;

	for (draws.Begin(); !draws.IsEnd(); draws.Next())
	{
		Lcddev* lcddev = lcddevs.Begin();

		if (NULL != lcddev)
		{
			lcddev->Flush(draws.Item()->area, draws.Item()->pixels);
		}
	}

	databus.draws.Release();
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
