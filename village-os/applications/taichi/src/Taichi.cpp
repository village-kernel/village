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


/// @brief Setup
void Taichi::Setup()
{

}


/// @brief Execute
void Taichi::Execute()
{
	ElfExecutor* simpleInput = new ElfExecutor();
	simpleInput->Run(ElfExecutor::_Background, "/applications/simpleInput.exec ps2keyboard ps2mouse");

	ElfExecutor* desktop = new ElfExecutor();
	desktop->Run(ElfExecutor::_Background, "/applications/desktop.exec display0");

	ElfExecutor* console = new ElfExecutor();
	console->Run(ElfExecutor::_Background, "/applications/console.exec serial0");

	while (1) {}
}


/// @brief main
int main(void)
{
	Taichi taichi;
	taichi.Setup();
	taichi.Execute();
	return 0;
}
