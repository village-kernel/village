//###########################################################################
// desktop_model.h
// Declarations of the desktop view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_MODEL_H__
#define __DESKTOP_MODEL_H__

#include "vg_villageui.h"


/// @brief DesktopModel
class DesktopModel : public Class
{
public:
	//Data
	char*      StartText;
	//Collection StartMenuLists;
	//Collection TaskbarLists;
	//Collection ContextMenuLists;
	//Collection ShortcutLists;

	//Command
	ICommand*  StartBtnCmd;
	ICommand*  StartMenuCmd;
	ICommand*  TaskbarCmd;
	ICommand*  ContextMenuCmd;
	ICommand*  ShortcutCmd;
public:
	//Methods
	DesktopModel();
	~DesktopModel();
private:
	//Command Methods
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
};

#endif //!__DESKTOP_MODEL_H__
