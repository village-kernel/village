//###########################################################################
// Start.cpp
//
// Top level singleton class that manages entire application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"
#include "Kernel.h"


///Main entry function
int main(void)
{
	System::Initialize();
	System::ConfigureMPU;
	System::ConfigurePower();
	System::ConfigureForXtal();

	Kernel::Initialize();
	Kernel::UpdateParams();
	Kernel::Execute();
}
