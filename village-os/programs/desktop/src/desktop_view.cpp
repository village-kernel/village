//###########################################################################
// desktop_view.cpp
// Definitions of the functions that manage desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desktop_view.h"


/// @brief InitComponent
void DesktopView::InitComponent(Wedget* parent)
{
	int width = parent->GetWidth();
	int height = parent->GetHeight();

	//Create context menu
	Menu* contextMenu = new Menu();
	contextMenu->SetSize(0, 0, 40, 40);
	contextMenu->SetBgColor(DrawDefs::_Blue);
	//contextMenu->SetItemSource(model.ContextMenuLists);
	contextMenu->BindingCommand(model.ContextMenuCmd);
	parent->AddWedget(contextMenu);

	//Create shortcut table
	Table* shortcut = new Table();
	shortcut->SetSize(0, 0, width, height - 40);
	shortcut->SetBgColor(DrawDefs::_Yellow);
	//shortcut->SetItemSource(model.ShortcutLists);
	shortcut->BindingCommand(model.ShortcutCmd);
	parent->AddWedget(shortcut);

	//Create start button
	Button* startBtn = new Button();
	startBtn->SetSize(0, height - 40, 40, 40);
	startBtn->SetBgColor(DrawDefs::_Brown);
	//startBtn->SetText(model.StartText);
	startBtn->BindingCommand(model.StartBtnCmd);
	parent->AddWedget(startBtn);

	//Create start menu
	Menu* startMenu = new Menu();
	startMenu->SetSize(0, height - 520, 320, 480);
	startMenu->SetBgColor(DrawDefs::_Lgray);
	startMenu->SetHidden(true);
	//startMenu->SetItemSource(model.StartMenuLists);
	startMenu->BindingCommand(model.StartMenuCmd);
	parent->AddWedget(startMenu);

	//Create task bar
	Toolbar* taskbar = new Toolbar();
	taskbar->SetSize(40, height - 40, width - 40, 40);
	taskbar->SetBgColor(DrawDefs::_Cyan);
	//taskbar->SetItemSource(model.TaskbarLists);
	taskbar->BindingCommand(model.TaskbarCmd);
	parent->AddWedget(taskbar);
}
