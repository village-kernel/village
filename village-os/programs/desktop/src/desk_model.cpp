//###########################################################################
// desk_model.cpp
// Definitions of the functions that manage desk view model
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "desk_model.h"
#include "vk_kernel.h"


/// @brief Constructor
DeskModel::DeskModel()
{

}


/// @brief Destructor
DeskModel::~DeskModel()
{
}


/// @brief 
/// @param name 
void DeskModel::OpenApplication(const char* name)
{
	kernel->process.Run(Process::_Background, name);
}


/// @brief 
/// @param name 
void DeskModel::ExitApplication(const char* name)
{

}
