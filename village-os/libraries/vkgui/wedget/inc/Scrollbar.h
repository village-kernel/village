//###########################################################################
// Scrollbar.h
// Declarations of the functions that manage scroll bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SCROLL_BAR_H__
#define __VK_SCROLL_BAR_H__

#include "Wedget.h"
#include "Button.h"


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
	void SetDirection(Direction dir);
	void InitContent();
};

#endif //!__VK_SCROLL_BAR_H__
