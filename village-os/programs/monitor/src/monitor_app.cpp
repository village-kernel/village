//###########################################################################
// monitor_app.cpp
// Definitions of the functions that manage monitor app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "monitor_app.h"
#include "vk_kernel.h"


/// @brief Constructor
MonitorApp::MonitorApp()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
MonitorApp::~MonitorApp()
{
}


/// @brief Setup
void MonitorApp::Setup()
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
	mainwin->SetSize(600, 400);
	mainwin->SetTitle((char*)"monitor");
	mainwin->SetBgColor(kernel->system.GetSysClkCounts());
	mainwin->ShowOnCenter();

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void MonitorApp::Execute()
{
	//Show main window
	mainwin->Show();
}


/// @brief Exit
void MonitorApp::Exit()
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
	MonitorApp monitor;
	monitor.Setup();
	monitor.Execute();
	monitor.Exit();
	return 0;
}
