//###########################################################################
// vg_table.h
// Declarations of the functions that manage table
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TABLE_H__
#define __VG_TABLE_H__

#include "vg_wedget.h"
#include "vg_button.h"


/// @brief VgTable
class VgTable : public VgWedget
{
private:
	//Members
	ICollection*        items;
	ICollection*        bItems;
	int                 index;
	IData<int>*         bIndex;
public:
	//Methods
	VgTable();
	~VgTable();

	//Binding Methods
	void BindingItems(ICollection* items);
	void SetItems(ICollection* items);
	ICollection* GetItems();

	void BindingItemIndex(IData<int>* index);
	void SetItemIndex(int index);
	int  GetItemIndex();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TABLE_H__
