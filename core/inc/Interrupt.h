//###########################################################################
// Interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "Templates.h"
#include "ArchInterrupt.h"

/// @brief Interrupt
class Interrupt
{
private:
	//Structures
	struct Isr
	{
		int32_t     irq;
		Function    func;
		void*       user;
		void*       args;

		Isr(int32_t irq = 0, Function func = NULL, void* user = NULL, void* args = NULL)
			:irq(irq),
			func(func),
			user(user),
			args(args)
		{}
	};

	//Members
	List<Isr>     isrTabs[ArchInterrupt::isr_num];
	ArchInterrupt archInterrupt;

	//Methods
	Interrupt();
	~Interrupt();
public:
	//Methods
	void Initialize();
	int SetISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int SetISR(int irq, Method method, Class* user, void* args = NULL);
	int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int AppendISR(int irq, Method method, Class* user, void* args = NULL);
	int RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int RemoveISR(int irq, Method method, Class* user, void* args = NULL);
	void ClearISR(int irq);

	//Interrupt handler
	void Handler(int irq);

	//Singleton Instance
	static Interrupt& Instance();
};

///Declarations interrupt reference
extern Interrupt& interrupt;

#endif //!__INTERRUPT_H__
