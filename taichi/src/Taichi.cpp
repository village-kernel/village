//###########################################################################
// Taichi.cpp
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Taichi.h"
#include "Village.h"
#include "Debug.h"


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
	debug.Info("taichi init");
}


/// @brief Execute
void Taichi::Execute()
{
	debug.Info("taichi execute");
	//village.Run("C:/applications/console.exec");
}


/// @brief main
extern "C" int main(void)
{
	Taichi taichi;
	taichi.Initialize();
	taichi.Execute();
	return 0;
}
