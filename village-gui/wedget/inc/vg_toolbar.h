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


/// @brief VgToolbar
class VgToolbar : public VgWedget
{
private:
	//Static constants members
	static const int item_axisx = 5;
	static const int item_axisy = 5;
	static const int item_span = 35;
	static const int item_width = 30;
	static const int item_height = 30;

	//Members
	ICollection*  items;
	ICollection*  bItems;
public:
	//Methods
	VgToolbar();
	~VgToolbar();

	//Attritube Methods
	void BindingItems(ICollection* items);
	void SetItems(ICollection* items);
	ICollection* GetItems();

	void AppendItem(CollectionItem* item);
	void RemoveItem(CollectionItem* item);

	void UpdateRequest(bool request);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TOOL_BAR_H__
