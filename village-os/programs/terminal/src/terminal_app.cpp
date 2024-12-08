//###########################################################################
// TerminalAPP.cpp
// Definitions of the functions that manage terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "terminal_app.h"
#include "vk_kernel.h"


/// @brief Constructor
TerminalAPP::TerminalAPP()
	:vkgui(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
TerminalAPP::~TerminalAPP()
{
}



/// @brief Create Window
/// @return 
Wedget* TerminalAPP::CreateWindow()
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
void TerminalAPP::DestroyWindow()
{
	vkgui->object.Destroy(mainwin);
}


/// @brief Setup
void TerminalAPP::Setup()
{
	//Create main window
	mainwin = CreateWindow();
	if (NULL == mainwin) return;

	//Setup mainwin size
	mainwin->SetSize(100, 100, 600, 400);
	mainwin->SetTitle((char*)"terminal");
	mainwin->SetBgColor(kernel->system.GetSysClkCounts());

	//Init view component
	view.InitComponent(mainwin);
}


/// @brief Execute
void TerminalAPP::Execute()
{
	//Show main window
	mainwin->Show();

	//Blocked app
	kernel->thread.Blocked();
}


/// @brief Exit
void TerminalAPP::Exit()
{
	DestroyWindow();
}


/// @brief main
int main(void)
{
	TerminalAPP terminal;
	terminal.Setup();
	terminal.Execute();
	terminal.Exit();
	return 0;
}
