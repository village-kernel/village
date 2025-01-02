//###########################################################################
// vg_villageui.cpp
// Definitions of the functions that manage village gui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_villageui.h"


/// @brief Constructor
VillageGUI::VillageGUI()
	:timer(devices),
	indevs(devices),
	displays(devices),
	mainwins(devices)
{
}


/// @brief Destructor
VillageGUI::~VillageGUI()
{
}


/// @brief Setup
void VillageGUI::Setup()
{
	//Setup timer
	timer.Setup();

	//Setup indevs
	indevs.Setup();

	//Setup displays
	displays.Setup();

	//Setup mainwins
	mainwins.Setup();
}


/// @brief Execute
void VillageGUI::Execute()
{
	//Execute timer
	timer.Execute();

	//Execute indevs
	indevs.Execute();

	//Execute displays
	displays.Execute();

	//Execute mainwins
	mainwins.Execute();
}


/// @brief Exit
void VillageGUI::Exit()
{
	//Exit mainwins
	mainwins.Exit();

	//Exit displays
	displays.Exit();

	//Exit indev
	indevs.Exit();

	//Exit timer
	timer.Exit();
}
