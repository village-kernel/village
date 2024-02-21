//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "System.h"
#include "Kernel.h"
#include "Hardware.h"


/// @brief ConcreteSystem
class ConcreteSystem : public System
{
private:
	//Members
	uint32_t sysTicks;
public:
	/// @brief Constructor
	ConcreteSystem()
		:sysTicks(0)
	{
	}


	/// @brief System Setup
	void Setup()
	{
		//Gets the interrupt pointer
		Interrupt* interrupt = (Interrupt*)kernel->modular->GetModule(ModuleID::_interrupt);

		//Set interrupt handler
		interrupt->SetISR(IRQ_Systick, (Method)&ConcreteSystem::SysTickHandler, this);

		//Configure clock
		ConfigureClock();
	}


	/// @brief Exit
	void Exit()
	{

	}


	/// @brief Configure clock
	void ConfigureClock()
	{
		//Reset systicks
		sysTicks = 0;

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


	///Delays for a specified number of milliseconds.
	void DelayMs(uint32_t millis)
	{
		uint32_t delayStart = sysTicks;
		uint32_t delayCycles = millis;
		while ((sysTicks - delayStart) < delayCycles);
	}


	/// @brief Reset x86 core
	void Reboot()
	{
		uint64_t null_idtr = 0;
		__asm volatile ("lidt %0; int3" :: "m" (null_idtr));

		//Loop with interrupt off if it doesn't work
		__asm volatile ("cli");
		while (1) { __asm volatile ("hlt"); }
	}


	/// @brief Enables IRQ interrupts
	void EnableIRQ() { __asm volatile("sti"); }


	/// @brief Disables IRQ interrupts
	void DisableIRQ() { __asm volatile("cli"); }


	/// @brief Get system clock count
	/// @return 
	uint32_t GetSysClkCounts() { return sysTicks; }


	/// @brief System clock counter
	void SysTickCounter() { sysTicks++; }
	
private:
	/// @brief System clock handler
	void SysTickHandler() { sysTicks++; }
};


///Register module
REGISTER_MODULE(ConcreteSystem, ModuleID::_system, system);
