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
	ContextCmd   = new RelayCommand(this, (Method)&DesktopModel::ContextClick);
	ShortcutCmd  = new RelayCommand(this, (Method)&DesktopModel::ShortcutClick);
	StartBtnCmd  = new RelayCommand(this, (Method)&DesktopModel::StartBtnClick);
	StartMenuCmd = new RelayCommand(this, (Method)&DesktopModel::StartMenuClick);
	ToolbarCmd   = new RelayCommand(this, (Method)&DesktopModel::ToolbarClick);
}


/// @brief Exit binding cmd
void DesktopModel::ExitBindingCmd()
{
	delete ContextCmd;
	delete ShortcutCmd;
	delete StartBtnCmd;
	delete StartMenuCmd;
	delete ToolbarCmd;
}


/// @brief Open application
/// @param name 
void DesktopModel::OpenApplication(const char* name)
{
	kernel->process.Run(Process::_Background, name);
}


/// @brief Exit application
/// @param name 
void DesktopModel::ExitApplication(const char* name)
{
	kernel->process.Kill(name);
}


/// @brief Context click
void DesktopModel::ContextClick(CollectionItem* item)
{

}


/// @brief Shortcut click
void DesktopModel::ShortcutClick(CollectionItem* item)
{
	
}


/// @brief Start btn click
void DesktopModel::StartBtnClick()
{
	StartMenuHidden->Set(!StartMenuHidden->Get());
}


/// @brief Start menu click
void DesktopModel::StartMenuClick(CollectionItem* item)
{

}


/// @brief Toolbar click
void DesktopModel::ToolbarClick(CollectionItem* item)
{
	OpenApplication((char*)item->data);
}
