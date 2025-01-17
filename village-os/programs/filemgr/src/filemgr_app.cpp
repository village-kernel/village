//###########################################################################
// filemgr_app.cpp
// Definitions of the functions that manage filemgr app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "filemgr_app.h"
#include "vk_kernel.h"


/// @brief Constructor
FilemgrApp::FilemgrApp()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
FilemgrApp::~FilemgrApp()
{
}


/// @brief Setup
void FilemgrApp::Setup()
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
	mainwin->SetTitle((char*)"filemgr");
	mainwin->SetBgColor(kernel->system.GetSysClkCounts());
	mainwin->ShowOnCenter();

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void FilemgrApp::Execute()
{
	//Show main window
	mainwin->Show();
}


/// @brief Exit
void FilemgrApp::Exit()
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
	FilemgrApp filemgr;
	filemgr.Setup();
	filemgr.Execute();
	filemgr.Exit();
	return 0;
}
