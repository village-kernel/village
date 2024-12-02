//###########################################################################
// TerminalApp.h
// Declarations of the terminal app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_APP_H__
#define __TERMINAL_APP_H__

#include "terminal_view.h"


/// @brief TerminalAPP
class TerminalAPP
{
private:
	//Members
	VkGraphics*  vkgui;
	Wedget*      mainwin;

	//Members
	TerminalView view;
private:
	//Methods
	Wedget* CreateWindow();
	void DestroyWindow();
public:
	//Methods
	TerminalAPP();
	~TerminalAPP();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__TERMINAL_APP_H__
