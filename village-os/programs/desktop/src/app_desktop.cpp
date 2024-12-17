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


/// @brief Create Window
/// @return 
Wedget* DesktopApp::CreateWindow()
{
	//Gets the vkgui module
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return NULL;

	//Gets the vkgui pointer
	vkgui = (VkGraphics*)module->GetData();
	if (NULL == vkgui) return NULL;
	
	//Create mainwin
	return vkgui->object.Create();
}


/// @brief Destroy Window
void DesktopApp::DestroyWindow()
{
	vkgui->object.Destroy(deskwin);
}


/// @brief Setup
void DesktopApp::Setup()
{
	//Create desk window
	deskwin = CreateWindow();
	if (NULL == deskwin) return;

	//Setup deskwin size
	deskwin->SetSize(0, 0, 1024, 728);
	deskwin->SetFixed(true);
	deskwin->SetAlwaysFocus(true);
	deskwin->SetPlace(Wedget::_Bottom);
	deskwin->SetTitle((char*)"desktop");

	//Init desk view component
	deskView.InitComponent(deskwin);

	//Create dock window
	dockwin = CreateWindow();
	if (NULL == dockwin) return;

	//Setup dock size
	dockwin->SetSize(0, 728, 1024, 40);
	dockwin->SetFixed(true);
	dockwin->SetAlwaysFocus(true);
	dockwin->SetPlace(Wedget::_Top);
	dockwin->SetTitle((char*)"dock");

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
	DestroyWindow();
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
