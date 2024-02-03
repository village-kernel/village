//###########################################################################
// Start.cpp
//
// Top level singleton class that manages kernel boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"


/// @brief Main entry function
int main(int argc, char* argv[])
{
	kernel->Initialize();
	kernel->UpdateParams();
	kernel->Execute();
	kernel->Exit();
	return _ERR;
}
