//###########################################################################
// monitor_app.h
// Declarations of the monitor app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MONITOR_APP_H__
#define __MONITOR_APP_H__

#include "monitor_view.h"


/// @brief MonitorApp
class MonitorApp
{
private:
	//Members
	VillageGUI*  vkgui;
	Window*      mainwin;

	//Members
	MonitorView view;
public:
	//Methods
	MonitorApp();
	~MonitorApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__MONITOR_APP_H__
