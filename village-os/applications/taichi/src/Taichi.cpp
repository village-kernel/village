//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Taichi.h"


/// @brief Constructor
Taichi::Taichi()
{
}


/// @brief Destructor
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
	//Execute simple input method
	kernel->process.Run(Process::_Background, "/applications/simpleInput.exec ps2keyboard ps2mouse");

	//Execute desktop
	kernel->process.Run(Process::_Background, "/applications/desktop.exec");
}


/// @brief main
int main(void)
{
	Taichi taichi;
	taichi.Setup();
	taichi.Execute();
	return 0;
}
