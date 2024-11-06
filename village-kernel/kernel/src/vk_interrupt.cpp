//###########################################################################
// vk_interrupt.cpp
// Definitions of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_interrupt.h"


/// @brief Constructor
ConcreteInterrupt::ConcreteInterrupt()
	:isReady(false)
{
}


/// @brief Destructor
ConcreteInterrupt::~ConcreteInterrupt()
{
}


/// @brief Interrupt Setup
void ConcreteInterrupt::Setup()
{
	//Setup exception
	exception.Setup();

	//Set ready flag
	isReady = true;

	//Output debug info
	kernel->debug.Info("Interrupt setup done!");
}


/// @brief Exit
void ConcreteInterrupt::Exit()
{
	isReady = false;

	for (uint32_t i = 0; i < Exception::isr_num; i++)
	{
		isrTabs[i].Release();
	}

	exception.Exit();
}


/// @brief Interrupt Set ISR, this will clean the isrTabs[irq]
/// @param irq irq number
/// @param func interupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int ConcreteInterrupt::SetISR(int irq, Function func, void* user, void* args)
{
	ClearISR(irq);
	irq += Exception::rsvd_isr_size;
	return isrTabs[irq].Add(new Isr(irq, func, user, args));
}


/// @brief Interrupt Set ISR, this will clean the isrTabs[irq]
/// @param irq irq number
/// @param method interupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int ConcreteInterrupt::SetISR(int irq, Method method, Class* user, void* args)
{
	return SetISR(irq, union_cast<Function>(method), (void*)user, args);
}


/// @brief Interrupt append ISR
/// @param irq irq number
/// @param func interupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int ConcreteInterrupt::AppendISR(int irq, Function func, void* user, void* args)
{
	irq += Exception::rsvd_isr_size;
	return isrTabs[irq].Add(new Isr(irq, func, user, args));
}


/// @brief Interrupt append ISR
/// @param irq irq number
/// @param method interupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int ConcreteInterrupt::AppendISR(int irq, Method method, Class* user, void* args)
{
	return AppendISR(irq, union_cast<Function>(method), (void*)user, args);
}


/// @brief Interrupt remove isr
/// @param irq irq number
/// @param func interrupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return Result::_OK / Result::_ERR
bool ConcreteInterrupt::RemoveISR(int irq, Function func, void* user, void* args)
{
	irq += Exception::rsvd_isr_size;

	List<Isr*>* isrs = &isrTabs[irq];

	for (Isr* isr = isrs->Begin(); !isrs->IsEnd(); isr = isrs->Next())
	{
		if ((irq  == isr->irq ) &&
			(func == isr->func) &&
			(user == isr->user) &&
			(args == isr->args))
		{
			return isrs->Remove(isr, isrs->GetNid());
		}
	}

	return false;
}


/// @brief Interrupt remove isr
/// @param irq irq number
/// @param method interrupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return Result::_OK / Result::_ERR
bool ConcreteInterrupt::RemoveISR(int irq, Method method, Class* user, void* args)
{
	return RemoveISR(irq, union_cast<Function>(method), (void*)user, args);
}


/// @brief Interrupt clear isr
/// @param irq irq number
/// @return Result::_OK / Result::_ERR
void ConcreteInterrupt::ClearISR(int irq)
{
	irq += Exception::rsvd_isr_size;

	List<Isr*>* isrs = &isrTabs[irq];

	for (Isr* isr = isrs->Begin(); !isrs->IsEnd(); isr = isrs->Next())
	{
		isrs->Remove(isr, isrs->GetNid());
	}
}


/// @brief Replace the stub_handler
/// @param irq 
/// @param handler 
void ConcreteInterrupt::Replace(int irq, uint32_t handler)
{
	irq += Exception::rsvd_isr_size;
	exception.Install(irq, handler);
}


/// @brief Interrupt handler
/// @param irq irq number
void ConcreteInterrupt::Handler(int irq)
{
	if (false == isReady) return;

	List<Isr*>* isrs = &isrTabs[irq];
	
	if (isrs->IsEmpty())
	{
		if (++warnings[irq] >= warning_times)
		{
			kernel->debug.Error("IRQ %d no being handled correctly, system will halt on here", irq);
			while(1) {}
		}
		kernel->debug.Warn("IRQ %d has no interrupt service function", irq);
		return;
	}
	else
	{
		warnings[irq] = 0;
	}

	for (Isr* isr = isrs->Begin(); !isrs->IsEnd(); isr = isrs->Next())
	{
		(isr->func)(isr->user, isr->args);
	}
}
