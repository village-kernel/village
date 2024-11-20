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
	display(sysinfo),
	object(sysinfo)
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

	//Setup display
	display.Setup();

	//Setup object
	object.Setup();
}


/// @brief Execute
void VkGraphics::Execute()
{
	//Execute timer
	timer.Execute();

	//Execute input
	input.Execute();

	//Execute display
	display.Execute();

	//Execute object
	object.Execute();
}


/// @brief Exit
void VkGraphics::Exit()
{
	//Exit object
	object.Exit();

	//Exit display
	display.Exit();

	//Exit indev
	input.Exit();

	//Exit timer
	timer.Exit();
}
