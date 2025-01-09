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
	bItems(NULL),
	index(0),
	bIndex(NULL)
{
	SetTitle((char*)"toolbar");
}


/// @brief Destructor
VgToolbar::~VgToolbar()
{
}


/// @brief VgToolbar binding items
/// @param items 
void VgToolbar::BindingItems(IData<Collection*>* items)
{
	bItems = items; if (bItems) bItems->Binding(this);
}


/// @brief VgToolbar set items
/// @param items 
void VgToolbar::SetItems(Collection* items)
{
	this->items = items; if (bItems) bItems->Set(items);
}


/// @brief VgToolbar get items
/// @return 
Collection* VgToolbar::GetItems()
{
	return bItems ? bItems->Get() : items;
}


/// @brief VgToolbar binding item index
/// @param index 
void VgToolbar::BindingItemIndex(IData<int>* index)
{
	bIndex = index; if (bIndex) bIndex->Binding(this);
}


/// @brief VgToolbar set item index
/// @param index 
void VgToolbar::SetItemIndex(int index)
{
	this->index = index; if (bIndex) bIndex->Set(index);
}


/// @brief VgToolbar get item index
/// @return 
int VgToolbar::GetItemIndex()
{
	return bIndex ? bIndex->Get() : index;
}


/// @brief VgToolbar initiate
/// @param devices 
void VgToolbar::InitContent(VgDevices* devices)
{

}


/// @brief VgToolbar execute
/// @param input 
void VgToolbar::ExecContent(VgInputData input)
{
	if (IsInLayerArea(input.point.x, input.point.y))
	{
		ExecuteCommand(input);
	}
}


/// @brief VgToolbar draw
/// @param drawArea 
void VgToolbar::DrawContent(VgDrawArea drawArea)
{

}
