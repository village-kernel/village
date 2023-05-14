//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Interrupt.h"
#include "Environment.h"
#include "System.h"


/// @brief Constructor
Interrupt::Interrupt()
	:isrSizes(0)
{
}


/// @brief Fini constructor
Interrupt::~Interrupt()
{
}


/// @brief Singleton Instance
/// @return Interrupt instance
Interrupt& Interrupt::Instance()
{
	static Interrupt instance;
	return instance;
}
EXPORT_SYMBOL(Interrupt::Instance, _ZN9Interrupt8InstanceEv);


/// @brief Definitions interrupt and export
Interrupt& interrupt = Interrupt::Instance();
Interrupt* pinterrupt = &interrupt;
EXPORT_SYMBOL(pinterrupt, interrupt);


/// @brief Interrupt initialize
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


/// @brief Interrupt Set ISR, this will clean the isrTabs[irq]
/// @param irq irq number
/// @param func interupt function
/// @param argv interrupt argv
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::SetISR(int irq, Function func, char* argv)
{
	ClearISR(irq);
	return isrTabs[irq].Add(new Isr(irq, func, argv));
}


/// @brief Interrupt append ISR
/// @param irq irq number
/// @param func interupt function
/// @param argv interrupt argv
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::AppendISR(int irq, Function func, char* argv)
{
	return isrTabs[irq].Add(new Isr(irq, func, argv));
}


/// @brief Interrupt remove isr
/// @param irq irq number
/// @param func interrupt function
/// @param argv interrupt argv
/// @return Result::_OK / Result::_ERR
int Interrupt::RemoveISR(int irq, Function func, char* argv)
{
	List<Isr> isrs = isrTabs[irq];

	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		if ((irq  == isr->irq ) &&
			(func == isr->func) &&
			(argv == isr->argv))
		{
			Result res = (Result)isrs.Remove(isr, isrs.GetNid());
			if (_OK == res) isrTabs[irq] = isrs;
			return res;
		}
	}

	return _ERR;
}


/// @brief Interrupt clear isr
/// @param irq irq number
/// @return Result::_OK / Result::_ERR
void Interrupt::ClearISR(int irq)
{
	List<Isr> isrs = isrTabs[irq];

	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		isrs.Remove(isr, isrs.GetNid());
	}

	isrTabs[irq] = isrs;
}

/// @brief Interrupt handler
/// @param irq irq number
void Interrupt::Handler(int irq)
{
	List<Isr> isrs = interrupt.isrTabs[irq - rsvd_isr_size];
	
	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		(isr->func)(isr->argv);
	}
}


/// @brief Default handler
__attribute__ ((naked)) void Interrupt::DefaultHandler()
{
	//Save LR back to main, must do this firstly
	__asm volatile("push {lr}");

	//Gets the ipsr value
	__asm volatile("mrs r0, ipsr");

	//Go to interrupt handler
	__asm volatile("bl _ZN9Interrupt7HandlerEi");

	//Exit
	__asm volatile("pop {lr}");
	__asm volatile("bx lr");
}
