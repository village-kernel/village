//###########################################################################
// vg_menu.h
// Declarations of the functions that manage menu
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_MENU_H__
#define __VG_MENU_H__

#include "vg_wedget.h"


/// @brief VgMenu
class VgMenu : public VgWedget
{
protected:
	//Members
	ICollection*  items;
	ICollection*  bItems;
	int           index;
	IData<int>*   bIndex;

	//Members
	ICommand*     itemCmd;
public:
	//Methods
	VgMenu();
	~VgMenu();

	//Command Methods
	void BindingItemCommand(ICommand* cmd);

	//Attritube Methods
	void BindingItems(ICollection* items);
	void SetItems(ICollection* items);
	ICollection* GetItems();

	void AppendItem(CollectionItem* item);
	void RemoveItem(CollectionItem* item);

	void BindingItemIndex(IData<int>* index);
	void SetItemIndex(int index);
	int  GetItemIndex();
};

#endif //!__VG_MENU_H__
