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
	screen(devices),
	group(devices)
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

	//Setup screen
	screen.Setup();

	//Setup group
	group.Setup();
}


/// @brief Execute
void VillageGUI::Execute()
{
	//Execute timer
	timer.Execute();

	//Execute input
	input.Execute();

	//Execute screen
	screen.Execute();

	//Execute group
	group.Execute();
}


/// @brief Exit
void VillageGUI::Exit()
{
	//Exit group
	group.Exit();

	//Exit screen
	screen.Exit();

	//Exit indev
	input.Exit();

	//Exit timer
	timer.Exit();
}
