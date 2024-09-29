//###########################################################################
// Taichi.cpp
// Definitions of the functions that manage taichi service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "TaichiService.h"
#include "Kernel.h"


/// @brief Constructor
TaichiService::TaichiService()
{
}


/// @brief Destructor
TaichiService::~TaichiService()
{
}


/// @brief Setup
void TaichiService::Setup()
{

}


/// @brief Execute
void TaichiService::Execute()
{
	//Execute input service
	kernel->process.Run(Process::_Background, "/services/input.exec");

	//Execute desktop
	kernel->process.Run(Process::_Background, "/applications/desktop.exec");
}


/// @brief main
int main(void)
{
	TaichiService taichi;
	taichi.Setup();
	taichi.Execute();
	return 0;
}
