//###########################################################################
// vg_table.cpp
// Definitions of the functions that manage table
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_table.h"


/// @brief Constructor
VgTable::VgTable()
	:items(NULL),
	bItems(NULL),
	index(0),
	bIndex(NULL)
{
	SetTitle((char*)"table");
}


/// @brief Destructor
VgTable::~VgTable()
{
}


/// @brief VgTable binding items
/// @param items 
void VgTable::BindingItems(IData<Collection*>* items)
{
	bItems = items; if (bItems) bItems->Binding(this);
}


/// @brief VgTable set items
/// @param items 
void VgTable::SetItems(Collection* items)
{
	this->items = items; if (bItems) bItems->Set(items);
}


/// @brief VgTable get items
/// @return 
Collection* VgTable::GetItems()
{
	return bItems ? bItems->Get() : items;
}


/// @brief VgTable binding item index
/// @param index 
void VgTable::BindingItemIndex(IData<int>* index)
{
	bIndex = index; if (bIndex) bIndex->Binding(this);
}


/// @brief VgTable set item index
/// @param index 
void VgTable::SetItemIndex(int index)
{
	this->index = index; if (bIndex) bIndex->Set(index);
}


/// @brief VgTable get item index
/// @return 
int VgTable::GetItemIndex()
{
	return bIndex ? bIndex->Get() : index;
}


/// @brief VgTable initiate
/// @param devices 
void VgTable::InitContent(VgDevices* devices)
{

}


/// @brief VgTable execute
/// @param input 
void VgTable::ExecContent(VgInputData input)
{
	if (IsInLayerArea(input.point.x, input.point.y))
	{
		ExecuteCommand(input);
	}
}


/// @brief VgTable draw
/// @param drawArea 
void VgTable::DrawContent(VgDrawArea drawArea)
{

}
