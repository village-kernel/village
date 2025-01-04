//###########################################################################
// settings_app.h
// Declarations of the settings app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SETTINGS_APP_H__
#define __SETTINGS_APP_H__

#include "settings_view.h"


/// @brief SettingsApp
class SettingsApp
{
private:
	//Members
	VillageGUI*  vkgui;
	Window*      mainwin;

	//Members
	SettingsView view;
public:
	//Methods
	SettingsApp();
	~SettingsApp();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__SETTINGS_APP_H__
