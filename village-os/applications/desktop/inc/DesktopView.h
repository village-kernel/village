//###########################################################################
// DesktopView.h
// Declarations of the desktop view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_VIEW_H__
#define __DESKTOP_VIEW_H__

#include "VkGUI.h"


/// @brief DesktopView
class DesktopView
{
private:
	//Members
	Window*  mainwin;
	Button*  startBtn;
	Toolbar* toolbar;
public:
	//Methods
	DesktopView();
	~DesktopView();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__DESKTOP_VIEW_H__
