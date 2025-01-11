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
	ICollection*  StartMenuItems;
	ICollection*  ToolbarItems;
	ICollection*  ContextItems;
	ICollection*  ShortcutItems;

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
	//Methods
	void InitBindingData();
	void ExitBindingData();
	void InitToolbarItems();
	void ExitToolbarItems();
	void InitBindingCmd();
	void ExitBindingCmd();
	void OpenApplication(const char* name);
	void ExitApplication(const char* name);
private:
	//Command Methods
	void ContextClick(CollectionItem* item);
	void ShortcutClick(CollectionItem* item);
	void StartBtnClick();
	void StartMenuClick(CollectionItem* item);
	void ToolbarClick(CollectionItem* item);
};

#endif //!__DESKTOP_MODEL_H__
