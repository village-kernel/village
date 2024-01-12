//###########################################################################
// Launch.cpp
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Launch.h"
#include "Village.h"


/// @brief Constructor
Launch::Launch()
{
}


/// @brief Deconstructor
Launch::~Launch()
{
}


/// @brief Initialize
void Launch::Initialize(const char* driver)
{
	gui.Initialize(driver);
}


/// @brief Execute
void Launch::Execute()
{
	gui.Printf("hello launch");
	while (1) {}
}


/// @brief main
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return _ERR;
	}
	else
	{
		Launch launch;
		launch.Initialize(argv[1]);
		launch.Execute();
		return _OK;
	}
}
