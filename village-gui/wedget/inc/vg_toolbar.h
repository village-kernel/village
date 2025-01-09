//###########################################################################
// vg_toolbar.h
// Declarations of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TOOL_BAR_H__
#define __VG_TOOL_BAR_H__

#include "vg_wedget.h"
#include "vg_button.h"
#include "vg_collection.h"


/// @brief VgToolbar
class VgToolbar : public VgWedget
{
private:
	//Members
	Collection*         items;
	IData<Collection*>* bItems;
	int                 index;
	IData<int>*         bIndex;
public:
	//Methods
	VgToolbar();
	~VgToolbar();

	//Binding Methods
	void BindingItems(IData<Collection*>* items);
	void SetItems(Collection* items);
	Collection* GetItems();

	void BindingItemIndex(IData<int>* index);
	void SetItemIndex(int index);
	int  GetItemIndex();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TOOL_BAR_H__
