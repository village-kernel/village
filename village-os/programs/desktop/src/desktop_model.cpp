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
	//StartText = (char*)"Start";

	//ShowMemuCmd = new RelayCommand(this, (Method)&DesktopModel::ShowStartMemu);

	//OpenAppCmd = new RelayCommand(this, (Method)&DesktopModel::OpenApplication);

	//ExitAppCmd = new RelayCommand(this, (Method)&DesktopModel::ExitApplication);

	StartBtnCmd = new RelayCommand(this, (Method)&DesktopModel::OpenApplication);
}


/// @brief Destructor
DesktopModel::~DesktopModel()
{
}


/// @brief 
/// @param name 
void DesktopModel::OpenApplication(const char* name)
{
	kernel->process.Run(Process::_Background, "/programs/terminal.exec");
}


/// @brief 
/// @param name 
void DesktopModel::ExitApplication(const char* name)
{

}
