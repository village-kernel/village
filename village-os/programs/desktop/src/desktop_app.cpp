//###########################################################################
// desktop_app.cpp
// Definitions of the functions that manage desktop app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desktop_app.h"
#include "vk_kernel.h"


/// @brief Constructor
DesktopApp::DesktopApp()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
DesktopApp::~DesktopApp()
{
}


/// @brief Setup
void DesktopApp::Setup()
{
	//Gets the vkgui module
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return;

	//Gets the vkgui pointer
	vkgui = (VillageGUI*)module->GetData();
	if (NULL == vkgui) return;
	
	//Create mainwin window
	mainwin = vkgui->group.Create();
	if (NULL == mainwin) return;

	//Setup mainwin size
	mainwin->SetSize(1024, 768);
	mainwin->SetFixed(true);
	mainwin->SetAlwaysFocus(true);
	mainwin->SetPlace(Window::_Bottom);
	mainwin->SetTitle((char*)"desktop");
	mainwin->SetHiddenNavbar(true);

	//Init desk view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void DesktopApp::Execute()
{
	//Show mainwin window
	mainwin->Show();
}


/// @brief Exit
void DesktopApp::Exit()
{
	//Wait for mainwin close
	while (vkgui->group.IsExist(mainwin)) 
	{
		kernel->thread.Sleep(1);
	}
}


/// @brief main
int main(int argc, char* argv[])
{
	DesktopApp desktop;
	desktop.Setup();
	desktop.Execute();
	desktop.Exit();
	return 0;
}
