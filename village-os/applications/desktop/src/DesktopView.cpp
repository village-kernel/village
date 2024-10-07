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
	Module* module = kernel->feature.GetModule("vkgui");
	if (NULL == module) return;

	VkGUI* vkgui = (VkGUI*)module->GetData();
	if (NULL == vkgui) return;
	
	mainwin = (Window*)vkgui->CreateMainWindow();

	startBtn = (Button*)mainwin->CreateWedget(Wedget::_Button);
	startBtn->Resize(0, mainwin->GetHeight() - 40, 40, 40);
	startBtn->SetText((char*)"Start");

	toolbar = (Toolbar*)mainwin->CreateWedget(Wedget::_Toolbar);
	toolbar->Resize(40, mainwin->GetHeight() - 40, mainwin->GetWidth() - 40, 40);
	toolbar->CreateItem("A");
	toolbar->CreateItem("B");
	toolbar->CreateItem("C");
	toolbar->CreateItem("D");

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
