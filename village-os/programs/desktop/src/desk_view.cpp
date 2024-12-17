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
	contextMenu->SetSize(0, 0, 40, 40);
	contextMenu->SetBgColor(DrawDefs::_Blue);
	//contextMenu->SetItemSource(model.ContextMenuLists);
	contextMenu->BindingCommand(model.ContextMenuCmd);
	parent->AddWedget(contextMenu);

	//Create shortcut table
	Table* shortcut = new Table();
	shortcut->SetSize(0, 0, width, height);
	shortcut->SetBgColor(DrawDefs::_Yellow);
	//shortcut->SetItemSource(model.ShortcutLists);
	shortcut->BindingCommand(model.ShortcutCmd);
	parent->AddWedget(shortcut);
}
