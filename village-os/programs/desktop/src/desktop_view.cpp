//###########################################################################
// desktop_view.cpp
// Definitions of the functions that manage desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desktop_view.h"


/// @brief InitComponent
void DesktopView::InitComponent(VgWedget* parent)
{
	int width = parent->GetWidth();
	int height = parent->GetHeight();

	//Create context menu
	VgContext* context = new VgContext();
	context->SetSize(80, 160);
	context->SetBgColor(VgDrawDefs::_White);
	context->SetHidden(true);
	context->BindingItems(model.ContextItems);
	context->BindingItemCommand(model.ContextItemCmd);
	parent->AddWedget(context);

	//Create shortcut table
	VgTable* shortcut = new VgTable();
	shortcut->SetSize(width, height - 40);
	shortcut->SetBgColor(VgDrawDefs::_Grayblue);
	shortcut->BindingItems(model.ShortcutItems);
	shortcut->BindingItemCommand(model.ShortcutItemCmd);
	parent->AddWedget(shortcut);

	//Create start button
	VgButton* startBtn = new VgButton();
	startBtn->AxisMove(0, height - 40);
	startBtn->SetSize(40, 40);
	startBtn->SetBgColor(VgDrawDefs::_Gray);
	startBtn->SetFloatable(true);
	startBtn->BindingText(model.StartBtnText);
	startBtn->BindingCommand(model.StartBtnCmd);
	parent->AddWedget(startBtn);

	//Create start menu
	VgTable* startMenu = new VgTable();
	startMenu->AxisMove(0, height - 520);
	startMenu->SetSize(320, 480);
	startMenu->SetBgColor(VgDrawDefs::_White);
	startMenu->SetFloatable(true);
	startMenu->BindingHidden(model.StartMenuHidden);
	startMenu->BindingItems(model.StartMenuItems);
	startMenu->BindingItemCommand(model.StartMenuItemCmd);
	parent->AddWedget(startMenu);

	//Create toolbar
	VgToolbar* toolbar = new VgToolbar();
	toolbar->AxisMove(40, height - 40);
	toolbar->SetSize(width - 40, 40);
	toolbar->SetBgColor(VgDrawDefs::_Lgray);
	toolbar->SetFloatable(true);
	toolbar->BindingItems(model.ToolbarItems);
	toolbar->BindingItemCommand(model.ToolbarItemCmd);
	parent->AddWedget(toolbar);
}
