//###########################################################################
// settings_view.h
// Declarations of the settings view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SETTINGS_VIEW_H__
#define __SETTINGS_VIEW_H__

#include "settings_model.h"

/// @brief SettingsView
class SettingsView
{
private:
	//Members
	SettingsModel model;
public:
	//Methods
	void InitComponent(VgWedget* parent);
};

#endif //!__SETTINGS_VIEW_H__
