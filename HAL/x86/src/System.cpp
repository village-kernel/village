//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"


///Initialize static members
uint32_t System::sysTicks = 0;
uint32_t System::cyclesInMicro = 8;


///Configure the SysTick timer
void System::Initialize(void)
{

}


///Configure memory protection unit
void System::ConfigureMPU()
{

}


///Configure the main internal regulator output voltage
void System::ConfigurePower()
{

}


///Configure clock
void System::ConfigureClock()
{

}


///System config vector table
void System::ConfigVectorTable(uint32_t vector)
{
	
}
