//###########################################################################
// dock_model.cpp
// Definitions of the functions that manage dock view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "dock_model.h"
#include "vk_kernel.h"


/// @brief Constructor
DockModel::DockModel()
{
	//StartText = (char*)"Start";

	//ShowMemuCmd = new RelayCommand(this, (Method)&DockModel::ShowStartMemu);

	//OpenAppCmd = new RelayCommand(this, (Method)&DockModel::OpenApplication);

	//ExitAppCmd = new RelayCommand(this, (Method)&DockModel::ExitApplication);

	StartBtnCmd = new RelayCommand(this, (Method)&DockModel::OpenApplication);
}


/// @brief Destructor
DockModel::~DockModel()
{
}


/// @brief 
/// @param name 
void DockModel::OpenApplication(const char* name)
{
	kernel->process.Run(Process::_Background, "/programs/terminal.exec");
}


/// @brief 
/// @param name 
void DockModel::ExitApplication(const char* name)
{

}
