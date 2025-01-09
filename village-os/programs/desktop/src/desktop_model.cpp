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
	StartBtnText      = new RelayData<char*>((char*)"Start");
	StartMenuHidden   = new RelayData<bool>(true);

	//Command
	ContextCmd   = new RelayCommand(this, (Method)&DesktopModel::ContextClick);
	ShortcutCmd  = new RelayCommand(this, (Method)&DesktopModel::ShortcutClick);
	StartBtnCmd  = new RelayCommand(this, (Method)&DesktopModel::StartBtnClick);
	StartMenuCmd = new RelayCommand(this, (Method)&DesktopModel::StartMenuClick);
	ToolbarCmd   = new RelayCommand(this, (Method)&DesktopModel::ToolbarClick);
}


/// @brief Destructor
DesktopModel::~DesktopModel()
{
	delete StartBtnText;
	delete StartMenuHidden;
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
void DesktopModel::ContextClick(const char* item)
{

}


/// @brief Shortcut click
void DesktopModel::ShortcutClick(const char* item)
{
	//kernel->debug.Info(item);
}


/// @brief Start btn click
void DesktopModel::StartBtnClick()
{
	StartMenuHidden->Set(!StartMenuHidden->Get());
}


/// @brief Start menu click
void DesktopModel::StartMenuClick(const char* item)
{

}


/// @brief Toolbar click
void DesktopModel::ToolbarClick(const char* item)
{
	//kernel->debug.Info(item);
}
