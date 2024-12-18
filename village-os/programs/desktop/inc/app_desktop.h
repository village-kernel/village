//###########################################################################
// app_desktop.h
// Declarations of the desktop app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_APP_H__
#define __DESKTOP_APP_H__

#include "desk_view.h"
#include "dock_view.h"


/// @brief DesktopApp
class DesktopApp
{
private:
	//Members
	VillageGUI*  vkgui;
	Window*      deskwin;
	Window*      dockwin;

	//Members
	DeskView     deskView;
	DockView     dockView;
private:
	//Methods
	Window* CreateWindow();
	void DestroyWindow();
public:
	//Methods
	DesktopApp();
	~DesktopApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__DESKTOP_APP_H__
