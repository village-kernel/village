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
	//contextMenu->SetItemSource(model.ContextMenuLists);
	contextMenu->SetCommand(model.ContextMenuCmd);
	parent->AddWedget(contextMenu);

	//Create shortcut table
	Table* shortcut = new Table();
	shortcut->SetSize(0, 0, height - 40, width - 40);
	//shortcut->SetItemSource(model.ShortcutLists);
	shortcut->SetCommand(model.ShortcutCmd);
	parent->AddWedget(shortcut);

	//Create start button
	Button* startBtn = new Button();
	startBtn->SetSize(0, height - 40, 40, 40);
	//startBtn->SetText(model.StartText);
	startBtn->SetCommand(model.StartBtnCmd);
	parent->AddWedget(startBtn);

	//Create start menu
	Menu* startMenu = new Menu();
	startBtn->SetSize(0, height - 520, 320, 480);
	//startBtn->SetItemSource(model.StartMenuLists);
	startBtn->SetCommand(model.StartMenuCmd);
	parent->AddWedget(startMenu);

	//Create task bar
	Toolbar* taskbar = new Toolbar();
	taskbar->SetSize(40, height - 40, width - 40, 40);
	//taskbar->SetItemSource(model.TaskbarLists);
	taskbar->SetCommand(model.TaskbarCmd);
	parent->AddWedget(taskbar);
}
