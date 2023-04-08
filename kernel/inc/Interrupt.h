//###########################################################################
// Interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "Templates.h"


//Interrupt
class Interrupt
{
private:
	//Structures
	struct IsrNode
	{
		int32_t     irq;
		Function    isr;
		char*       argv;
		IsrNode*    next;

		IsrNode(int32_t irq = 0, Function isr = NULL, char* argv = NULL)
			:irq(irq),
			isr(isr),
			argv(argv),
			next(NULL)
		{}
	};

	//Static constants
	static const uint32_t rsvd_isr_size = 16;

	//Members
	uint32_t  isrSizes;
	uint32_t* vectors;
	IsrNode** lists;

	//Methods
	Interrupt();
	static void Handler(int irq);
	static void DefaultHandler();
public:
	//Methods
	void Initialize();
	void SetISR(int irq, Function isr, char* argv = NULL);
	void ClearISR(int irq, Function isr, char* argv = NULL);

	//Singleton Instance
	static Interrupt& Instance();
};

///Declarations interrupt reference
extern Interrupt& interrupt;

#endif //!__INTERRUPT_H__
