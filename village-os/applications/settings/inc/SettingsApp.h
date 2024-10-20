//###########################################################################
// SettingsApp.h
// Declarations of the settings app
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SETTINGS_APP_H__
#define __SETTINGS_APP_H__

#include "SettingsView.h"


/// @brief SettingsApp
class SettingsApp
{
private:
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
