//###########################################################################
// app_desktop.cpp
// Definitions of the functions that manage desktop app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "app_desktop.h"
#include "vk_kernel.h"


/// @brief Constructor
DesktopApp::DesktopApp()
	:vkgui(NULL),
	deskwin(NULL),
	dockwin(NULL)
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
	
	//Create desk window
	deskwin = vkgui->group.Create();
	if (NULL == deskwin) return;

	//Setup deskwin size
	deskwin->SetSize(1024, 728);
	deskwin->SetFixed(true);
	deskwin->SetAlwaysFocus(true);
	deskwin->SetPlace(Window::_Bottom);
	deskwin->SetTitle((char*)"desktop");
	deskwin->SetHiddenNavbar(true);

	//Init desk view component
	deskView.InitComponent(deskwin);

	//Create dock window
	dockwin = vkgui->group.Create();
	if (NULL == dockwin) return;

	//Setup dock size
	dockwin->AxisMove(0, 728);
	dockwin->SetSize(1024, 40);
	dockwin->SetFixed(true);
	dockwin->SetAlwaysFocus(true);
	dockwin->SetPlace(Window::_Top);
	dockwin->SetTitle((char*)"dock");
	dockwin->SetHiddenNavbar(true);

	//Init dock view component
	dockView.InitComponent(dockwin);
}


/// @brief Execute
void DesktopApp::Execute()
{
	//Show desk window
	deskwin->Show();

	//Show dock window
	dockwin->Show();

	//Blocked app
	kernel->thread.Blocked();
}


/// @brief Exit
void DesktopApp::Exit()
{
	
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
