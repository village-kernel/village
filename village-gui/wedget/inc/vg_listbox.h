//###########################################################################
// vg_listbox.h
// Declarations of the functions that manage list box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LIST_BOX_H__
#define __VG_LIST_BOX_H__

#include "vg_wedget.h"


/// @brief VgListBox
class VgListBox : public VgWedget
{
public:
	//Methods
	VgListBox();
	~VgListBox();

	//Binding Methods
	void BindingItems(ICollection* items);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_LIST_BOX_H__
