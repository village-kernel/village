//###########################################################################
// vg_listbox.h
// Declarations of the functions that manage list box
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_LIST_BOX_H__
#define __VG_LIST_BOX_H__

#include "vg_wedget.h"


/// @brief ListBox
class ListBox : public Wedget
{
public:
	//Methods
	ListBox();
	~ListBox();

	void InitContent();
	void DrawContent();
};

#endif //!__VG_LIST_BOX_H__
