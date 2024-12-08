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


/// @brief Scrollbar
class Scrollbar : public Wedget
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
	Button* scrollbtn;
public:
	//Methods
	Scrollbar();
	~Scrollbar();

	void SetDirection(Direction dir);
};

#endif //!__VG_SCROLL_BAR_H__
