//###########################################################################
// vg_graphics.cpp
// Definitions of the functions that manage village gui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_graphics.h"


/// @brief Constructor
VkGraphics::VkGraphics()
	:timer(data),
	input(data),
	group(data),
	display(data)
{
}


/// @brief Destructor
VkGraphics::~VkGraphics()
{
}


/// @brief Setup
void VkGraphics::Setup()
{
	//Setup timer
	timer.Setup();

	//Setup input
	input.Setup();

	//Setup group
	group.Setup();

	//Setup display
	display.Setup();
}


/// @brief Execute
void VkGraphics::Execute()
{
	//Execute timer
	timer.Execute();

	//Execute input
	input.Execute();

	//Execute group
	group.Execute();

	//Execute display
	display.Execute();
}


/// @brief Exit
void VkGraphics::Exit()
{
	//Exit display
	display.Exit();

	//Exit group
	group.Exit();

	//Exit indev
	input.Exit();

	//Exit timer
	timer.Exit();
}
