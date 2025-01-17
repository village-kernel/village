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
	ICommand*  StartBtnCmd;
	ICommand*  ToolbarItemCmd;
	ICommand*  ContextItemCmd;
	ICommand*  ShortcutItemCmd;
	ICommand*  StartMenuItemCmd;
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
private:
	//Command Methods
	void StartBtnClick();
	void ToolbarItemClick(CollectionItem* item);
	void ContextItemClick(CollectionItem* item);
	void ShortcutItemClick(CollectionItem* item);
	void StartMenuItemClick(CollectionItem* item);
};

#endif //!__DESKTOP_MODEL_H__
