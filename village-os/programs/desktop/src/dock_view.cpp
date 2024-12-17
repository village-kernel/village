//###########################################################################
// dock_view.cpp
// Definitions of the functions that manage dock view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "dock_view.h"


/// @brief InitComponent
void DockView::InitComponent(Wedget* parent)
{
	int width = parent->GetWidth();

	//Create start button
	Button* startBtn = new Button();
	startBtn->SetSize(0, 0, 40, 40);
	startBtn->SetBgColor(DrawDefs::_Brown);
	//startBtn->SetText(model.StartText);
	startBtn->BindingCommand(model.StartBtnCmd);
	parent->AddWedget(startBtn);

	//Create start menu
	Menu* startMenu = new Menu();
	startMenu->SetSize(0, -480, 320, 480);
	startMenu->SetBgColor(DrawDefs::_Lgray);
	startMenu->SetHidden(true);
	//startMenu->SetItemSource(model.StartMenuLists);
	startMenu->BindingCommand(model.StartMenuCmd);
	parent->AddWedget(startMenu);

	//Create task bar
	Toolbar* taskbar = new Toolbar();
	taskbar->SetSize(40, 0, width - 40, 40);
	taskbar->SetBgColor(DrawDefs::_Cyan);
	//taskbar->SetItemSource(model.TaskbarLists);
	taskbar->BindingCommand(model.TaskbarCmd);
	parent->AddWedget(taskbar);
}
