//###########################################################################
// vg_gui.cpp
// Definitions of the functions that manage village gui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_gui.h"


/// @brief Constructor
VillageGUI::VillageGUI()
	:timer(devices),
	input(devices),
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

	//Setup input
	input.Setup();

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

	//Execute input
	input.Execute();

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
	input.Exit();

	//Exit timer
	timer.Exit();
}
