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
	Context* context = new Context();
	context->SetSize(80, 160);
	context->SetBgColor(DrawDefs::_White);
	context->SetHidden(true);
	//context->SetItemSource(model.ContextMenuLists);
	context->BindingCommand(model.ContextMenuCmd);
	parent->AddWedget(context);

	//Create shortcut table
	Table* shortcut = new Table();
	shortcut->SetSize(width, height);
	shortcut->SetBgColor(DrawDefs::_Gray);
	//shortcut->SetItemSource(model.ShortcutLists);
	shortcut->BindingCommand(model.ShortcutCmd);
	parent->AddWedget(shortcut);

	//Create start button
	Button* startBtn = new Button();
	startBtn->AxisMove(0, height - 40);
	startBtn->SetSize(40, 40);
	startBtn->SetBgColor(DrawDefs::_Brown);
	startBtn->SetFloatable(true);
	//startBtn->SetText(model.StartText);
	startBtn->BindingCommand(model.StartBtnCmd);
	parent->AddWedget(startBtn);

	//Create start menu
	Menu* startMenu = new Menu();
	startMenu->AxisMove(0, height - 520);
	startMenu->SetSize(320, 480);
	startMenu->SetBgColor(DrawDefs::_Lgray);
	startMenu->SetFloatable(true);
	startMenu->SetHidden(true);
	//startMenu->SetItemSource(model.StartMenuLists);
	startMenu->BindingCommand(model.StartMenuCmd);
	parent->AddWedget(startMenu);

	//Create task bar
	Toolbar* taskbar = new Toolbar();
	taskbar->AxisMove(40, height - 40);
	taskbar->SetSize(width - 40, 40);
	taskbar->SetBgColor(DrawDefs::_Cyan);
	taskbar->SetFloatable(true);
	//taskbar->SetItemSource(model.TaskbarLists);
	taskbar->BindingCommand(model.TaskbarCmd);
	parent->AddWedget(taskbar);
}
