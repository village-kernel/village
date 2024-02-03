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
	ElfExecutor* launch = new ElfExecutor();
	launch->Run(ElfExecutor::_Background, "/applications/launch.exec display0");

	ElfExecutor* console = new ElfExecutor();
	console->Run(ElfExecutor::_Background, "/applications/console.exec serial0");

	while (1) {}
}


/// @brief Kernel
Kernel* kernel;


/// @brief setup
/// @param kernel 
/// @return 
extern "C" void setup(void* knl)
{
	kernel = (Kernel*)knl;
}


/// @brief main
int main(void)
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
	return 0;
}
