//###########################################################################
// DesktopView.cpp
// Definitions of the functions that manage desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DesktopView.h"
#include "Kernel.h"


/// @brief Constructor
DesktopView::DesktopView()
	:mainwin(NULL),
	startBtn(NULL),
	toolbar(NULL)
{
}


/// @brief Destructor
DesktopView::~DesktopView()
{
	Exit();
}


/// @brief Setup
void DesktopView::Setup()
{
	//Gets the vkgui module
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return;

	//Gets the vkgui pointer
	VkGUI* vkgui = (VkGUI*)module->GetData();
	if (NULL == vkgui) return;
	
	//Create mainwin
	mainwin = (Window*)vkgui->CreateMainWindow();

	//Create start button
	startBtn = new Button();
	startBtn->SetSize(0, mainwin->GetHeight() - 40, 40, 40);
	startBtn->SetText((char*)"Start");
	mainwin->AddWedget(startBtn);

	//Create tool bar
	toolbar = new Toolbar();
	toolbar->SetSize(40, mainwin->GetHeight() - 40, mainwin->GetWidth() - 40, 40);
	toolbar->AddItem("A");
	toolbar->AddItem("B");
	toolbar->AddItem("C");
	toolbar->AddItem("D");
	mainwin->AddWedget(toolbar);

	//Showing
	mainwin->Showing();
}


/// @brief Exit
void DesktopView::Exit()
{

}


/// @brief Execute
void DesktopView::Execute()
{
	if (NULL != mainwin)
	{
		mainwin->Refresh();
		kernel->thread.Sleep(1);
	}
}
