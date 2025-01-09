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
	IData<char*>* StartBtnText;
	IData<bool>*  StartMenuHidden;

	//Collection
	IData<Collection*>*  StartMenuItems;
	IData<Collection*>*  ToolbarItems;
	IData<Collection*>*  ContextItems;
	IData<Collection*>*  ShortcutItems;

	//Command
	ICommand*  ContextCmd;
	ICommand*  ShortcutCmd;
	ICommand*  StartBtnCmd;
	ICommand*  StartMenuCmd;
	ICommand*  ToolbarCmd;
public:
	//Methods
	DesktopModel();
	~DesktopModel();
private:
	//Command Methods
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
	void ContextClick(const char* item);
	void ShortcutClick(const char* item);
	void StartBtnClick();
	void StartMenuClick(const char* item);
	void ToolbarClick(const char* item);
};

#endif //!__DESKTOP_MODEL_H__
