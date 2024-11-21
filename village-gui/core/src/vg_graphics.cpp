//###########################################################################
// vg_graphics.cpp
// Definitions of the functions that manage village gui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_graphics.h"


/// @brief Constructor
VkGraphics::VkGraphics()
	:timer(sysinfo),
	input(sysinfo),
	object(sysinfo),
	display(sysinfo)
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

	//Setup object
	object.Setup();

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

	//Execute object
	object.Execute();

	//Execute display
	display.Execute();
}


/// @brief Exit
void VkGraphics::Exit()
{
	//Exit display
	display.Exit();

	//Exit object
	object.Exit();

	//Exit indev
	input.Exit();

	//Exit timer
	timer.Exit();
}
