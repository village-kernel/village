//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"
#include "Kernel.h"


///Initialize static members
uint32_t System::sysTicks = 0;


///Configure the SysTick timer
void System::Initialize(void)
{
	//Set interrupt handler
	Kernel::interrupt.SetISR(IRQ_Systick, union_cast<Function>(&System::SysTickCounter));
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
	//Get the PIT value: hardware clock at 1193182 Hz
	uint32_t freq = 1000; //1000hz, 1ms
	uint32_t divider = 1193182 / freq;
	uint8_t low  = low_8(divider);
	uint8_t high = high_8(divider);

	//Send the command
	PortByteOut(TIMER_CMD, 0x36); //Command port
	PortByteOut(TIMER_CH0, low);
	PortByteOut(TIMER_CH0, high);
}
