//###########################################################################
// Toolbar.h
// Declarations of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TOOL_BAR_H__
#define __VK_TOOL_BAR_H__

#include "Wedget.h"
#include "Button.h"


/// @brief Toolbar
class Toolbar : public Wedget
{
private:
	//Members
	int itemSize;
public:
	//Methods
	Toolbar();
	~Toolbar();
	void AddItem(const char* name);
};

#endif //!__VK_TOOL_BAR_H__
