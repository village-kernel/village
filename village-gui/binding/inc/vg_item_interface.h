//###########################################################################
// vg_item_interface.h
// Declarations of the functions that manage item interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_ITEM_INTERFACE__H__
#define __VG_ITEM_INTERFACE__H__

#include "stdint.h"


/// @brief VgWedget
class VgWedget;


/// @brief CollectionItem
struct CollectionItem
{
	char* name;
	void* data;
};


/// @brief ICollection
class ICollection
{
public:
	//Destructor
	virtual ~ICollection() {}

	//Methods
	virtual void Binding(VgWedget* wedget) = 0;
	
	virtual void Begin() = 0;
	virtual bool IsEnd() = 0;
	virtual void Next() = 0;
	virtual CollectionItem* Item() = 0;

	virtual void Append(CollectionItem* item) = 0;
	virtual void Remove(CollectionItem* item) = 0;

	virtual CollectionItem* GetItem(int index) = 0;
	virtual int GetSize() = 0;
};

#endif //!__VG_ITEM_INTERFACE__H__
