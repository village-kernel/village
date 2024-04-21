//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Taichi.h"
#include "ElfExecutor.h"


/// @brief Constructor
Taichi::Taichi()
{
}


/// @brief Deconstructor
Taichi::~Taichi()
{
}


/// @brief Initialize
void Taichi::Initialize()
{

}


/// @brief Execute
void Taichi::Execute()
{
	ElfExecutor* desktop = new ElfExecutor();
	desktop->Run(ElfExecutor::_Background, "/applications/desktop.exec display0 ps2keyboard ps2mouse");

	ElfExecutor* console = new ElfExecutor();
	console->Run(ElfExecutor::_Background, "/applications/console.exec serial0");

	while (1) {}
}


/// @brief main
int main(void)
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
	return 0;
}
