//###########################################################################
// vg_menu.cpp
// Definitions of the functions that manage menu
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_menu.h"


/// @brief Constructor
VgMenu::VgMenu()
	:items(NULL),
	bItems(NULL),
	index(0),
	bIndex(NULL),
	itemCmd(NULL)
{
	SetTitle((char*)"menu");
}


/// @brief Destructor
VgMenu::~VgMenu()
{
}


/// @brief VgMenu binding item command
/// @param cmd 
void VgMenu::BindingItemCommand(ICommand* cmd)
{
	this->itemCmd = cmd;
}


/// @brief VgMenu binding items
/// @param items 
void VgMenu::BindingItems(ICollection* items)
{
	bItems = items; if (bItems) bItems->Binding(this);
}


/// @brief VgMenu set items
/// @param items 
void VgMenu::SetItems(ICollection* items)
{
	this->items = items;
}


/// @brief VgMenu get items
/// @return 
ICollection* VgMenu::GetItems()
{
	return bItems ? bItems : items;
}


/// @brief VgMenu append item
/// @param item 
void VgMenu::AppendItem(CollectionItem* item)
{
	ICollection* items = GetItems();
	if (items) items->Append(item);
}


/// @brief VgMenu remove item
/// @param item 
void VgMenu::RemoveItem(CollectionItem* item)
{
	ICollection* items = GetItems();
	if (items) items->Remove(item);
}


/// @brief VgMenu binding item index
/// @param index 
void VgMenu::BindingItemIndex(IData<int>* index)
{
	bIndex = index; if (bIndex) bIndex->Binding(this);
}


/// @brief VgMenu set item index
/// @param index 
void VgMenu::SetItemIndex(int index)
{
	this->index = index; if (bIndex) bIndex->Set(index);
}


/// @brief VgMenu get item index
/// @return 
int VgMenu::GetItemIndex()
{
	return bIndex ? bIndex->Get() : index;
}
