//###########################################################################
// manager_app.cpp
// Definitions of the functions that manage manager app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "manager_app.h"
#include "vk_kernel.h"


/// @brief Constructor
ManagerApp::ManagerApp()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
ManagerApp::~ManagerApp()
{
}


/// @brief Setup
void ManagerApp::Setup()
{
	//Gets the vkgui module
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return;

	//Gets the vkgui pointer
	vkgui = (VillageGUI*)module->GetData();
	if (NULL == vkgui) return;
	
	//Create mainwin
	mainwin = vkgui->mainwins.Create();
	if (NULL == mainwin) return;

	//Setup mainwin size
	mainwin->AxisMove(100, 100);
	mainwin->SetSize(600, 400);
	mainwin->SetTitle((char*)"manager");
	mainwin->SetBgColor(kernel->system.GetSysClkCounts());

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void ManagerApp::Execute()
{
	//Show main window
	mainwin->Show();
}


/// @brief Exit
void ManagerApp::Exit()
{
	//Wait for mainwin close
	while (vkgui->mainwins.IsExist(mainwin)) 
	{
		kernel->thread.Sleep(1);
	}
}


/// @brief main
int main(void)
{
	ManagerApp manager;
	manager.Setup();
	manager.Execute();
	manager.Exit();
	return 0;
}
