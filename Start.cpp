//###########################################################################
// Start.cpp
//
// Top level singleton class that manages kernel boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"
#include "Kernel.h"


///Main entry function
int main(void)
{
	System::Initialize();
	System::ConfigureMPU();
	System::ConfigurePower();
	System::ConfigureClock();

	Kernel::Initialize();
	Kernel::UpdateParams();
	Kernel::Execute();
}
