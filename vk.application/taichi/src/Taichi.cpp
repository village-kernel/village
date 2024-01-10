//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Taichi.h"


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
	executor.Run(Executor::_Foreground, "/applications/console.exec serial");
}


/// @brief main
extern "C" int main(void)
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
	return 0;
}
