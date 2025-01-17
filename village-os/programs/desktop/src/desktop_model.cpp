//###########################################################################
// desktop_model.cpp
// Definitions of the functions that manage desktop view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desktop_model.h"
#include "vk_kernel.h"


/// @brief Constructor
DesktopModel::DesktopModel()
{
	//Data
	InitBindingData();

	//Collection
	InitToolbarItems();

	//Command
	InitBindingCmd();
}


/// @brief Destructor
DesktopModel::~DesktopModel()
{
	//Data
	ExitBindingData();

	//Collection
	ExitToolbarItems();

	//Command
	ExitBindingCmd();
}


/// @brief Init binding data
void DesktopModel::InitBindingData()
{
	StartBtnText    = new BindingData<char*>((char*)"Start");
	StartMenuHidden = new BindingData<bool>(true);
}


/// @brief Exit binding data
void DesktopModel::ExitBindingData()
{
	delete StartBtnText;
	delete StartMenuHidden;
}


/// @brief toolbarItems
CollectionItem toolbarItems[] = {
	{ (char*)">_", (void*)"/programs/terminal.exec" },
	{ (char*)"M",  (void*)"/programs/monitor.exec"  },
	{ (char*)"F",  (void*)"/programs/filemgr.exec"  },
	{ (char*)"S",  (void*)"/programs/settings.exec" },
};


/// @brief Init toolbar items
void DesktopModel::InitToolbarItems()
{
	ToolbarItems = new BindingCollection();

	int toolbarItemSize = sizeof(toolbarItems) / sizeof(toolbarItems[0]);

	for (int i = 0; i < toolbarItemSize; i++)
	{
		ToolbarItems->Append(&toolbarItems[i]);
	}
}


/// @brief Exit toolbar items
void DesktopModel::ExitToolbarItems()
{
	delete ToolbarItems;
}


/// @brief Init binding cmd
void DesktopModel::InitBindingCmd()
{
	StartBtnCmd      = new RelayCommand(this, (Method)&DesktopModel::StartBtnClick);
	ToolbarItemCmd   = new RelayCommand(this, (Method)&DesktopModel::ToolbarItemClick);
	ContextItemCmd   = new RelayCommand(this, (Method)&DesktopModel::ContextItemClick);
	ShortcutItemCmd  = new RelayCommand(this, (Method)&DesktopModel::ShortcutItemClick);
	StartMenuItemCmd = new RelayCommand(this, (Method)&DesktopModel::StartMenuItemClick);
}


/// @brief Exit binding cmd
void DesktopModel::ExitBindingCmd()
{
	delete StartBtnCmd;
	delete ToolbarItemCmd;
	delete ContextItemCmd;
	delete ShortcutItemCmd;
	delete StartMenuItemCmd;
}


/// @brief Start btn click
void DesktopModel::StartBtnClick()
{
	StartMenuHidden->Set(!StartMenuHidden->Get());
}


/// @brief Toolbar item click
void DesktopModel::ToolbarItemClick(CollectionItem* item)
{
	kernel->process.Run(Process::_Background, (char*)item->data);
}


/// @brief Context menu item click
void DesktopModel::ContextItemClick(CollectionItem* item)
{

}


/// @brief Shortcut item click
void DesktopModel::ShortcutItemClick(CollectionItem* item)
{
	
}


/// @brief Start menu item click
void DesktopModel::StartMenuItemClick(CollectionItem* item)
{

}
