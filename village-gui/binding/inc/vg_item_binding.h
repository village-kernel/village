//###########################################################################
// vg_item_binding.h
// Declarations of the functions that manage item binding
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_ITEM_BINDING_H__
#define __VG_ITEM_BINDING_H__

#include "vg_item_interface.h"
#include "vg_list.h"
#include "vg_wedget.h"


/// @brief BindingCollection
class BindingCollection : public ICollection
{
private:
	//Members
	VgList<CollectionItem*> items;
	VgWedget* wedget;
public:
	/// @brief Constructor
	BindingCollection()
		:wedget(NULL)
	{
	}

	/// @brief Binding wedget
	/// @param wedget 
	void Binding(VgWedget* wedget)
	{
		this->wedget = wedget;
	}

	/// @brief Begin
	void Begin()
	{
		items.Begin();
	}

	/// @brief IsEnd
	/// @return 
	bool IsEnd()
	{
		return items.IsEnd();
	}

	/// @brief Next
	void Next()
	{
		items.Next();
	}

	/// @brief Item
	/// @return 
	CollectionItem* Item()
	{
		return items.Item();
	}

	/// @brief Append item
	/// @param value 
	void Append(CollectionItem* item)
	{
		items.Add(item);
		if (wedget) wedget->UpdateRequest(true);
	}

	/// @brief Remove item
	/// @return 
	void Remove(CollectionItem* item)
	{
		items.Remove(item);
		if (wedget) wedget->UpdateRequest(true);
	}

	/// @brief Get ttem
	/// @param index 
	/// @return 
	CollectionItem* GetItem(int index)
	{
		return items.GetItem(index);
	}

	/// @brief Get size
	/// @return 
	int GetSize()
	{
		return items.GetSize();
	}
};

#endif //!__VG_ITEM_BINDING_H__
