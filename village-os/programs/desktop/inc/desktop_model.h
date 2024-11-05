//###########################################################################
// desktop_model.h
// Declarations of the desktop view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_MODEL_H__
#define __DESKTOP_MODEL_H__

#include "vg_graphics.h"
#include "vg_input_cmd.h"


/// @brief DesktopModel
class DesktopModel : public Class
{
public:
	////Data
	//char*      StartText;
	//Collection ContextMenuLists;
	//Collection ShortcutLists;
	//Collection StartMenuLists;
	//Collection TaskbarLists;

	////Command
	//ICommand*  ContextMenuCmd;
	//ICommand*  ShortcutCmd;
	//ICommand*  StartBtnCmd;
	//ICommand*  StartMenuCmd;
	//ICommand*  TaskbarCmd;
public:
	//Methods
	DesktopModel();
	~DesktopModel();
private:
	//Command Methods
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
};

#endif //!__DESKTOP_VIEW_MODEL_H__
