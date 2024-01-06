//###########################################################################
// ArchInterrupt.cpp
// Definitions of the functions that manage arch interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "ArchInterrupt.h"
#include "Interrupt.h"
#include "Environment.h"
#include "System.h"

/// @brief Declarations
extern "C" void IRQ_Handler(uint32_t irq);
extern "C" void Stub_Handler();
extern "C" void Default_Handler();


/// @brief Constructor
ArchInterrupt::ArchInterrupt()
{
}


/// @brief Fini constructor
ArchInterrupt::~ArchInterrupt()
{
}


/// @brief Interrupt initialize
void ArchInterrupt::Initialize()
{
	//Symbol defined in the linker script
	extern void *_sivector, *_svector, *_evector;

	//Copy isr vector from sivector
	void **pSource = &_sivector, **pDest = &_svector;
	for (; pDest != &_evector; pSource++, pDest++)
		*pDest = *pSource;

	//Calculate the size of isr vector
	isrSizes = ((uint32_t)&_evector - (uint32_t)&_svector) >> 2;
	isrSizes = isrSizes - rsvd_isr_size;

	//Calculate the address of usr isr vectors
	vectors = (uint32_t*)&_svector + rsvd_isr_size;

	//Set the new isr handler
	for (uint32_t i = 0; i < isrSizes; i++)
	{
		//Change the origin handler into isr table
		if (vectors[i] != (uint32_t)&(Default_Handler) + 1)
		{
			interrupt.SetISR(i, (Function)vectors[i], NULL, NULL);
		}

		vectors[i] = (uint32_t)&Stub_Handler;
	}

	//Relocation isr vecotr table
	System::ConfigVectorTable((uint32_t)&_svector);
}


/// @brief IRQ handler
/// @param irq 
extern "C" void IRQ_Handler(uint32_t irq)
{
	Interrupt::Instance().Handler(irq - ArchInterrupt::rsvd_isr_size);
}


/// @brief Default handler
extern "C"  __attribute__ ((naked)) void Stub_Handler()
{
	//Save LR back to main, must do this firstly
	__asm volatile("push {lr}");

	//Gets the ipsr value
	__asm volatile("mrs r0, ipsr");

	//Go to interrupt handler
	__asm volatile("bl IRQ_Handler");

	//Exit
	__asm volatile("pop {lr}");
	__asm volatile("bx lr");
}
