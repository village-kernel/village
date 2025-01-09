//###########################################################################
// vg_scrollbar.h
// Declarations of the functions that manage scroll bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_SCROLL_BAR_H__
#define __VG_SCROLL_BAR_H__

#include "vg_wedget.h"
#include "vg_button.h"


/// @brief VgScrollbar
class VgScrollbar : public VgWedget
{
public:
	//Direction
	enum Direction
	{
		_Vertical = 0,
		_Horizontal,
	};
private:
	//Members
	Direction dir;
	VgButton* scrollbtn;
public:
	//Methods
	VgScrollbar();
	~VgScrollbar();

	void SetDirection(Direction dir);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_SCROLL_BAR_H__
