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
public:
	//Methods
	VgMenu();
	~VgMenu();

	//Binding Methods
	void BindingItems(ICollection* items);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_MENU_H__
