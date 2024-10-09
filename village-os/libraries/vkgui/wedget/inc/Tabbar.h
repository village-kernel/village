//###########################################################################
// Tabbar.h
// Declarations of the functions that manage tab bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TAB_BAR_H__
#define __VK_TAB_BAR_H__

#include "Wedget.h"
#include "Button.h"


/// @brief Tabbar
class Tabbar : public Wedget
{
private:
	//Members
	int itemSize;
public:
	//Methods
	Tabbar();
	~Tabbar();
	void AddItem(const char* name);
};

#endif //!__VK_TAB_BAR_H__
