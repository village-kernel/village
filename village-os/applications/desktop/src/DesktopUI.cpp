//###########################################################################
// DesktopUI.cpp
// Definitions of the functions that manage desktop ui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "DesktopUI.h"
#include "Kernel.h"


/// @brief Constructor
DesktopUI::DesktopUI()
	:mainwin(NULL)
{
}


/// @brief Destructor
DesktopUI::~DesktopUI()
{
	Exit();
}


/// @brief Setup
void DesktopUI::Setup()
{
	if (false == SetupWin()) return;

	kernel->inputEvent.Attach(InputEvent::_OutputAxis, (Method)&DesktopUI::UpdateAxis, this);
}


/// @brief Exit
void DesktopUI::Exit()
{
	kernel->inputEvent.Detach(InputEvent::_OutputAxis, (Method)&DesktopUI::UpdateAxis, this);
	graphics.Exit();
}


/// @brief SetupWin
bool DesktopUI::SetupWin()
{
	if (false == graphics.Setup()) return false;

	mainwin = (Window*)graphics.CreateMainWindow();

	tabbar = (Tabbar*)mainwin->CreateWedget(Wedget::_Tabbar);
	tabbar->SetLocation(0, mainwin->GetHeight() - 40, mainwin->GetWidth(), 40);

	button0 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button0->SetLocation(0, 0, 40, 40);
	button0->SetText((char*)"Start");

	button1 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button1->SetLocation(50, 5, 30, 30);
	button1->SetText((char*)"A");

	button2 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button2->SetLocation(90, 5, 30, 30);
	button2->SetText((char*)"B");

	button3 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button3->SetLocation(130, 5, 30, 30);
	button3->SetText((char*)"C");

	button4 = (Button*)tabbar->CreateWedget(Wedget::_Button);
	button4->SetLocation(170, 5, 30, 30);
	button4->SetText((char*)"D");

	cursor = (Cursor*)mainwin->CreateWedget(Wedget::_Cursor);
	cursor->SetLocation(0, 0, mainwin->GetWidth(), mainwin->GetHeight());

	mainwin->Show();

	return true;
}


/// @brief Update location axis
void DesktopUI::UpdateAxis(InputEvent::OutputAxis* input)
{
	cursor->Update(input->axisX, input->axisY);
}


/// @brief Execute
void DesktopUI::Execute()
{
	if (NULL != mainwin)
	{
		mainwin->Refresh();
	}
}