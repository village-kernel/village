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
}
