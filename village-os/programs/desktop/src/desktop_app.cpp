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


/// @brief Create Window
/// @return 
Window* DesktopApp::CreateWindow()
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
	vkgui->object.Destroy(mainwin);
}


/// @brief Setup
void DesktopApp::Setup()
{
	//Create main window
	mainwin = CreateWindow();
	if (NULL == mainwin) return;

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void DesktopApp::Execute()
{
	//Show main window
	mainwin->Show();

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
