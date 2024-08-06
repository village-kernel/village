//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Interrupt.h"
#include "Hardware.h"
#include "Registers.h"
#include "Kernel.h"


/// @brief Declarations
extern "C" void Default_Handler();


/// @brief Exception Setup
void Exception::Setup()
{
	//Symbol defined in the linker script
	extern void *_sivector, *_svector, *_evector;

	//Copy isr vector from sivector
	void **pSource = &_sivector, **pDest = &_svector;
	for (; pDest != &_evector; pSource++, pDest++)
		*pDest = *pSource;

	//Calculate the size of isr vector
	uint32_t isrSizes = ((uint32_t)&_evector - (uint32_t)&_svector) >> 2;

	//Calculate the address of usr isr vectors
	volatile uint32_t* vectors = (uint32_t*)&_svector;

	//Set the new isr handler
	for (uint32_t i = 0; i < isrSizes; i++)
	{
		//Change the origin handler into isr table
		if (vectors[i] != (uint32_t)&Default_Handler)
		{
			kernel->interrupt.SetISR(i - rsvd_isr_size, (Function)vectors[i], NULL, NULL);
		}

		//Offset _estack and Reset_Handler
		if (i >= 2) vectors[i] = (uint32_t)&Exception::StubHandler;
	}

	//Install handlers
	InstallHandlers();

	//Relocation isr vecotr table
	ConfigVectorTable((uint32_t)&_svector);
}


/// @brief Exception Exit
void Exception::Exit()
{
}


/// @brief Exception install handlers
void Exception::InstallHandlers()
{
	kernel->interrupt.Replace(NonMaskableInt_IRQn,     (uint32_t)&Exception::NMIHandler         );
	kernel->interrupt.Replace(HardFault_IRQn,          (uint32_t)&Exception::HardFaultHandler   );
	kernel->interrupt.Replace(MemoryManagement_IRQn,   (uint32_t)&Exception::MemManageHandler   );
	kernel->interrupt.Replace(BusFault_IRQn,           (uint32_t)&Exception::BusFaultHandler    );
	kernel->interrupt.Replace(UsageFault_IRQn,         (uint32_t)&Exception::UsageFaultHandler  );
	kernel->interrupt.Replace(DebugMonitor_IRQn,       (uint32_t)&Exception::DebugMonHandler    );
}


/// @brief Install irq handler
/// @param irq 
/// @param handler 
void Exception::Install(int irq, uint32_t handler)
{
	//Symbol defined in the linker script
	extern void *_svector;

	//Calculate the address of usr isr vectors
	volatile uint32_t* vectors = (uint32_t*)&_svector;

	//Replace irq handler
	vectors[irq] = handler;
}


/// @brief System config vector table, this value must be a multiple of 0x200.
void Exception::ConfigVectorTable(uint32_t vector)
{
	SCB->VTOR = vector;
}


/// @brief Stub Handler
void Exception::StubHandler()
{
	uint32_t irq = 0;

	//Gets the ipsr value
	__asm volatile("mrs %0, ipsr" : "+r"(irq));

	//Handle the interrupt in a more modular way
	kernel->interrupt.Handler(irq);
}


/// @brief Exception Info
/// @param exception 
#define ExceptionInfo(exception)                   \
{                                                  \
	const char* excep = exception;                 \
	__asm volatile("tst lr, #4");                  \
	__asm volatile("ite eq");                      \
	__asm volatile("mrseq r0, msp");               \
	__asm volatile("mrsne r0, psp");               \
	__asm volatile("stmdb r0!, {r4-r11}");         \
	__asm volatile("mov r1, %0" : "+r"(excep));    \
	__asm volatile("b StackedInfo");               \
}


/// @brief NMIHandler
void __attribute__ ((naked)) Exception::NMIHandler()
{
	ExceptionInfo("NMI Handler");
}


/// @brief HardFaultHandler
void __attribute__ ((naked)) Exception::HardFaultHandler()
{
	ExceptionInfo("Hard Fault Handler");
}


/// @brief MemManageHandler
void __attribute__ ((naked)) Exception::MemManageHandler()
{
	ExceptionInfo("Mem Manage Handler");
}


/// @brief BusFaultHandler
void __attribute__ ((naked)) Exception::BusFaultHandler()
{
	ExceptionInfo("Bus Fault Handler");
}


/// @brief UsageFaultHandler
void __attribute__ ((naked)) Exception::UsageFaultHandler()
{
	ExceptionInfo("Usage Fault Handler");
}


/// @brief DebugMonHandler
void __attribute__ ((naked)) Exception::DebugMonHandler()
{
	ExceptionInfo("Debug Mon Handler");
}


/// @brief Output stacked info
/// @param regs stack pointer
extern "C" void StackedInfo(Registers* regs, char* exception)
{
	kernel->debug.Error("r0:   0x%08lx", regs->r0);
	kernel->debug.Error("r1:   0x%08lx", regs->r1);
	kernel->debug.Error("r2:   0x%08lx", regs->r2);
	kernel->debug.Error("r3:   0x%08lx", regs->r3);
	kernel->debug.Error("r4:   0x%08lx", regs->r4);
	kernel->debug.Error("r5:   0x%08lx", regs->r5);
	kernel->debug.Error("r6:   0x%08lx", regs->r6);
	kernel->debug.Error("r7:   0x%08lx", regs->r7);
	kernel->debug.Error("r8:   0x%08lx", regs->r8);
	kernel->debug.Error("r9:   0x%08lx", regs->r9);
	kernel->debug.Error("r10:  0x%08lx", regs->r10);
	kernel->debug.Error("r11:  0x%08lx", regs->r11);
	kernel->debug.Error("r12:  0x%08lx", regs->r12);
	kernel->debug.Error("lr:   0x%08lx", regs->lr);
	kernel->debug.Error("pc:   0x%08lx", regs->pc);
	kernel->debug.Error("xpsr: 0x%08lx", regs->xpsr);
	kernel->debug.Error(exception);
	while(1) {}
}
