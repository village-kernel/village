//###########################################################################
// vg_tabbar.h
// Declarations of the functions that manage tab bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TAB_BAR_H__
#define __VG_TAB_BAR_H__

#include "vg_wedget.h"


/// @brief VgTabbar
class VgTabbar : public VgWedget
{
public:
	//Methods
	VgTabbar();
	~VgTabbar();
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_TAB_BAR_H__
