//###########################################################################
// ArchInterrupt.cpp
// Definitions of the functions that manage arch interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "ArchInterrupt.h"
#include "Interrupt.h"
#include "Hardware.h"
#include "Kernel.h"


/// @brief Declarations
extern "C" void Stub_Handler();
extern "C" void Default_Handler();


/// @brief Interrupt Setup
void ArchInterrupt::Setup()
{
	//Symbol defined in the linker script
	extern void *_sivector, *_svector, *_evector;

	//Copy isr vector from sivector
	void **pSource = &_sivector, **pDest = &_svector;
	for (; pDest != &_evector; pSource++, pDest++)
		*pDest = *pSource;

	//Calculate the size of isr vector, offset _estack and Reset_Handler
	uint32_t isrSizes = ((uint32_t)&_evector - (uint32_t)&_svector) >> 2;
	isrSizes = isrSizes - 2;

	//Calculate the address of usr isr vectors, offset _estack and Reset_Handler
	uint32_t* vectors = (uint32_t*)&_svector + 2;

	//Set the new isr handler
	for (uint32_t i = 0; i < isrSizes; i++)
	{
		//Change the origin handler into isr table, offset _estack and Reset_Handler
		if (vectors[i] != (uint32_t)&(Default_Handler) + 1)
		{
			int irq = i - (rsvd_isr_size - 2);
			kernel->interrupt.SetISR(irq, (Function)vectors[i], NULL, NULL);
		}

		vectors[i] = (uint32_t)&Stub_Handler;
	}

	//Relocation isr vecotr table
	ConfigVectorTable((uint32_t)&_svector);
}


/// @brief Exit
void ArchInterrupt::Exit()
{

}


/// @brief System config vector table, this value must be a multiple of 0x200.
void ArchInterrupt::ConfigVectorTable(uint32_t vector)
{
	SCB->VTOR = vector;
}


/// @brief Output stacked info
/// @param regs stack pointer
extern "C" void StackedInfo(Registers* regs)
{
	kernel->debug.Error("Hard_Fault_Handler:");
	kernel->debug.Error("irq:  0x%08lx", regs->irq);
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
}


/// @brief IRQ handler
/// @param regs 
extern "C" void IRQ_Handler(Registers* regs)
{
	//Output stacked info
	if (regs->irq >= 2 && regs->irq <= 13)
	{
		StackedInfo(regs);
	}

	//Handle the interrupt in a more modular way
	kernel->interrupt.Handler(regs->irq);
}


/// @brief Stub_Handler
extern "C" void __attribute__ ((naked)) Stub_Handler() 
{
	//Save LR back to main
	__asm volatile("push {lr}");

	//Save IPSR to sp
	__asm volatile("mrs r0, ipsr");
	__asm volatile("push {r0}");

	//Save r4-r11 regs to sp
	__asm volatile("stmdb sp!, {r4-r11}");

	//Call IRQ_Handler(sp)
	__asm volatile("mov r0, sp");
	__asm volatile("bl IRQ_Handler");

	//Retrieve r4-r11 regs from sp
	__asm volatile("ldmia sp!, {r4-r11}");

	//Skip ipsr
	__asm volatile("add sp, sp, #4");

	//Exit
	__asm volatile("pop {lr}");
	__asm volatile("bx lr");
}
