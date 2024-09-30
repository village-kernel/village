//###########################################################################
// GuiService.cpp
// Definitions of the functions that manage gui service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "GuiService.h"


/// @brief Constructor
GuiService::GuiService()
{
} 


/// @brief Destructor
GuiService::~GuiService()
{
}


/// @brief Setup
void GuiService::Setup()
{
	vkgui.SetID(ModuleID::_serivce);
	vkgui.SetName((char*)"vkgui");
	kernel->feature.RegisterModule(&vkgui);
}


/// @brief Execute
void GuiService::Execute()
{
	kernel->thread.ChangeState(Thread::_Blocked);

	while(1) {}
}


/// @brief Exit
void GuiService::Exit()
{
	kernel->feature.UnregisterModule(&vkgui);
}


/// @brief main
int main(int argc, char* argv[])
{
	GuiService gui;
	gui.Setup();
	gui.Execute();
	gui.Exit();
	return 0;
}
