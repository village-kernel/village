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

	//Calculate the size of isr vector
	uint32_t isrSizes = ((uint32_t)&_evector - (uint32_t)&_svector) >> 2;

	//Calculate the address of usr isr vectors
	uint32_t* vectors = (uint32_t*)&_svector;

	//Set the new isr handler
	for (uint32_t i = 0; i < isrSizes; i++)
	{
		//Change the origin handler into isr table
		if (vectors[i] != (uint32_t)&Default_Handler)
		{
			kernel->interrupt.SetISR(i - rsvd_isr_size, (Function)vectors[i], NULL, NULL);
		}

		//Offset _estack and Reset_Handler
		if (i >= 2) vectors[i] = (uint32_t)&ArchInterrupt::StubHandler;
	}

	//Relocation isr vecotr table
	ConfigVectorTable((uint32_t)&_svector);
}


/// @brief Install irq handler
/// @param irq 
/// @param handler 
void ArchInterrupt::Install(int irq, uint32_t handler)
{
	//Symbol defined in the linker script
	extern void *_svector;

	//Calculate the address of usr isr vectors
	uint32_t* vectors = (uint32_t*)&_svector;

	//Replace irq handler
	vectors[irq] = handler;
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


/// @brief Stub_Handler
void ArchInterrupt::StubHandler()
{
	uint32_t irq = 0;

	//Gets the ipsr value
	__asm volatile("mrs %0, ipsr" : "+r"(irq));

	//Handle the interrupt in a more modular way
	kernel->interrupt.Handler(irq);
}
