//###########################################################################
// vg_toolbar.cpp
// Definitions of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_toolbar.h"


/// @brief Constructor
VgToolbar::VgToolbar()
	:items(NULL),
	bItems(NULL)
{
	SetTitle((char*)"toolbar");
}


/// @brief Destructor
VgToolbar::~VgToolbar()
{
}


/// @brief VgToolbar binding items
/// @param items 
void VgToolbar::BindingItems(ICollection* items)
{
	bItems = items; if (bItems) bItems->Binding(this);
}


/// @brief VgToolbar set items
/// @param items 
void VgToolbar::SetItems(ICollection* items)
{
	this->items = items;
}


/// @brief VgToolbar get items
/// @return 
ICollection* VgToolbar::GetItems()
{
	return bItems ? bItems : items;
}


/// @brief VgToolbar append item
/// @param item 
void VgToolbar::AppendItem(CollectionItem* item)
{
	ICollection* items = GetItems();
	if (items) items->Append(item);
}


/// @brief VgToolbar remove item
/// @param item 
void VgToolbar::RemoveItem(CollectionItem* item)
{
	ICollection* items = GetItems();
	if (items) items->Remove(item);
}


/// @brief VgToolbar update request
/// @param request 
void VgToolbar::UpdateRequest(bool request)
{
	VgWedget::UpdateRequest(request);
}


/// @brief VgToolbar initiate
/// @param devices 
void VgToolbar::InitContent(VgDevices* devices)
{
	ICollection* items = GetItems();

	if (items)
	{
		int xspan = 0;

		for (items->Begin(); !items->IsEnd(); items->Next())
		{
			CollectionItem* item = items->Item();

			VgButton* button = new VgButton();
			button->AxisMove(xspan + item_axisx, item_axisy);
			button->SetSize(item_width, item_height);
			button->SetBgColor(VgDrawDefs::_White);
			button->SetText((char*)item->name);
			button->SetArgs((void*)item);
			button->BindingCommand(cmd);
			AddWedget(button);

			xspan += item_span;
		}
	}
}


/// @brief VgToolbar execute
/// @param input 
void VgToolbar::ExecContent(VgInputData input)
{

}


/// @brief VgToolbar draw
/// @param drawArea 
void VgToolbar::DrawContent(VgDrawArea drawArea)
{

}
