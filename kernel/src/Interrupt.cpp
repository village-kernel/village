//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Interrupt.h"
#include "Environment.h"
#include "System.h"


///Constructor
Interrupt::Interrupt()
	:isrSizes(0)
{
}


///Singleton instance
Interrupt& Interrupt::Instance()
{
	static Interrupt instance;
	return instance;
}
EXPORT_SYMBOL(Interrupt::Instance, _ZN9Interrupt8InstanceEv);


///Definitions interrupt and export
Interrupt& interrupt = Interrupt::Instance();
Interrupt* pinterrupt = &interrupt;
EXPORT_SYMBOL(pinterrupt, interrupt);


///Interrupt initialize
void Interrupt::Initialize()
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

	//Alloc lists heap
	isrTabs = (List<Isr>*)new List<Isr>[isrSizes]();

	//Relocation isr vecotr table
	System::ConfigVectorTable((uint32_t)&_svector);
}


///Interrupt Set ISR
void Interrupt::SetISR(int irq, Function func, char* argv)
{
	isrTabs[irq].Add(new Isr(irq, func, argv));
	vectors[irq] = union_cast<uint32_t>(&Interrupt::DefaultHandler);
}


///Interrupt clear isr
void Interrupt::ClearISR(int irq, Function func, char* argv)
{
	List<Isr> isr = isrTabs[irq];

	for (isr.Begin(); !isr.IsEnd(); isr.Next())
	{
		if ((irq  == isr.Item()->irq ) &&
			(func == isr.Item()->func) &&
			(argv == isr.Item()->argv))
		{
			isr.Remove(isr.Item(), isr.GetNid()); break;
		}
	}
}


///Interrupt handler
void Interrupt::Handler(int irq)
{
	List<Isr> isr = interrupt.isrTabs[irq - rsvd_isr_size];
	
	for (isr.Begin(); !isr.IsEnd(); isr.Next())
	{
		(isr.Item()->func)(isr.Item()->argv);
	}
}


///Default handler
__attribute__ ((naked)) void Interrupt::DefaultHandler()
{
	//Save LR back to main, must do this firstly
	__ASM("push {lr}");

	//Gets the ipsr value
	__ASM("mrs r0, ipsr");

	//Go to interrupt handler
	__ASM("bl _ZN9Interrupt7HandlerEi");

	//Exit
	__ASM("pop {lr}");
	__ASM("bx lr");
}
