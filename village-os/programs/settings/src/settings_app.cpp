//###########################################################################
// SettingsApp.cpp
// Definitions of the functions that manage settings app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "settings_app.h"
#include "vk_kernel.h"


/// @brief Constructor
SettingsApp::SettingsApp()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
SettingsApp::~SettingsApp()
{
}


/// @brief Setup
void SettingsApp::Setup()
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
	mainwin->SetTitle((char*)"settings");
	mainwin->SetBgColor(kernel->system.GetSysClkCounts());

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void SettingsApp::Execute()
{
	//Show main window
	mainwin->Show();
}


/// @brief Exit
void SettingsApp::Exit()
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
	SettingsApp settings;
	settings.Setup();
	settings.Execute();
	settings.Exit();
	return 0;
}
