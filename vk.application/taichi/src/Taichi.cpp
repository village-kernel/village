//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Taichi.h"
#include "Executor.h"


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
	Executor* launch = new Executor();
	launch->Run(Executor::_Background, "/applications/launch.exec display");

	Executor* console = new Executor();
	console->Run(Executor::_Background, "/applications/console.exec serial");

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
