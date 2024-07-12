//###########################################################################
// Settings.cpp
// The overall framework of the Settings
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Settings.h"


/// @brief Constructor
Settings::Settings()
{
}


/// @brief Destructor
Settings::~Settings()
{
}


/// @brief Setup
void Settings::Setup()
{

}


/// @brief Execute
void Settings::Execute()
{
	int counter = 0;
	while (1) 
	{
		kernel->debug.Log("hello settings counter %d", counter++);
		kernel->thread.Sleep(2000);
	}
}


/// @brief main
int main(void)
{
	Settings settings;
	settings.Setup();
	settings.Execute();
	return 0;
}
