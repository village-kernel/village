//###########################################################################
// TerminalView.cpp
// Definitions of the functions that manage terminal view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TerminalView.h"
#include "Kernel.h"


/// @brief Constructor
TerminalView::TerminalView()
	:mainwin(NULL),
	navbar(NULL),
	textbox(NULL)
{
}


/// @brief Destructor
TerminalView::~TerminalView()
{
}


/// @brief Setup
void TerminalView::Setup()
{
	//Gets the vkgui module
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return;

	//Gets the vkgui pointer
	VkGUI* vkgui = (VkGUI*)module->GetData();
	if (NULL == vkgui) return;

	//Create mainwin
	mainwin = (Window*)vkgui->CreateMainWindow();
	mainwin->SetSize(20, 20, mainwin->GetWidth() - 40, mainwin->GetHeight() - 100);
	
	//Create navbar
	navbar = new Navbar();
	navbar->SetSize(0, 0, mainwin->GetWidth(), 20);
	navbar->SetTitile((char*)"terminal");
	mainwin->AddWedget(navbar);

	//Create textbox
	textbox = new TextBox();
	textbox->SetSize(0, 20, mainwin->GetWidth(), mainwin->GetHeight() - 20);
	mainwin->AddWedget(textbox);

	//Showing
	mainwin->Showing();
}


/// @brief Execute
void TerminalView::Execute()
{
	if (NULL != mainwin)
	{
		mainwin->Refresh();
		kernel->thread.Sleep(1);
	}
}


/// @brief Exit
void TerminalView::Exit()
{

}


/// @brief 
/// @param data 
/// @param size 
/// @return 
int TerminalView::Input(uint8_t* data, uint32_t size)
{
	return textbox->AppendText((char*)data, size);
}


/// @brief 
/// @param data 
/// @param size 
/// @return 
int TerminalView::Output(uint8_t* data, uint32_t size)
{
	return textbox->OutputData((char*)data, size);
}
