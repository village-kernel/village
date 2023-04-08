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
	:isrSizes(0),
	lists(NULL)
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
	lists = (IsrNode**)new IsrNode[isrSizes]();

	//Relocation isr vecotr table
	System::ConfigVectorTable((uint32_t)&_svector);
}


///Interrupt Set ISR
void Interrupt::SetISR(int irq, Function isr, char* argv)
{
	if (0 > irq && NULL == isr) return;

	IsrNode** nextNode = &lists[irq];

	while (NULL != *nextNode) nextNode = &(*nextNode)->next;

	*nextNode = new IsrNode(irq, isr, argv);

	vectors[irq] = union_cast<uint32_t>(&Interrupt::DefaultHandler);
}


///Interrupt clear isr
void Interrupt::ClearISR(int irq, Function isr, char* argv)
{
	IsrNode** prevNode = &lists[irq];
	IsrNode** currNode = &lists[irq];

	while (NULL != *currNode)
	{
		if ((irq == (*currNode)->irq) &&
			(isr == (*currNode)->isr) &&
			(argv == (*currNode)->argv))
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}


///Interrupt handler
void Interrupt::Handler(int irq)
{
	IsrNode* node = interrupt.lists[irq - rsvd_isr_size];
	for (; NULL != node; node = node->next)
	{
		(node->isr)(node->argv);
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
