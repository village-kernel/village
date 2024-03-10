//###########################################################################
// Start.cpp
//
// Top level singleton class that manages kernel boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"


/// @brief Main entry function
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[])
{
	kernel->Setup();
	kernel->Start();
	kernel->Exit();
	return 0;
}
