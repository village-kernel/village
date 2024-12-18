//###########################################################################
// desk_view.cpp
// Definitions of the functions that manage desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desk_view.h"


/// @brief InitComponent
void DeskView::InitComponent(Wedget* parent)
{
	int width = parent->GetWidth();
	int height = parent->GetHeight();

	//Create context menu
	Menu* contextMenu = new Menu();
	contextMenu->SetSize(40, 40);
	contextMenu->SetBgColor(DrawDefs::_Blue);
	contextMenu->SetHidden(true);
	//contextMenu->SetItemSource(model.ContextMenuLists);
	contextMenu->BindingCommand(model.ContextMenuCmd);
	parent->AddWedget(contextMenu);

	//Create shortcut table
	Table* shortcut = new Table();
	shortcut->SetSize(width, height);
	shortcut->SetBgColor(DrawDefs::_Gray);
	//shortcut->SetItemSource(model.ShortcutLists);
	shortcut->BindingCommand(model.ShortcutCmd);
	parent->AddWedget(shortcut);
}
