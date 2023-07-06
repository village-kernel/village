//###########################################################################
// Interrupt.cpp
// Definitions of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Interrupt.h"
#include "ArchInterrupt.h"
#include "Environment.h"
#include "Debug.h"


/// @brief Constructor
Interrupt::Interrupt()
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
EXPORT_SYMBOL(_ZN9Interrupt8InstanceEv);


/// @brief Definitions interrupt and export
Interrupt& interrupt = Interrupt::Instance();
EXPORT_SYMBOL(interrupt);


/// @brief Interrupt initialize
void Interrupt::Initialize()
{
	archInterrupt.Initialize();
}


/// @brief Interrupt Set ISR, this will clean the isrTabs[irq]
/// @param irq irq number
/// @param func interupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::SetISR(int irq, Function func, void* user, void* args)
{
	ClearISR(irq);
	return isrTabs[irq].Add(new Isr(irq, func, user, args));
}
EXPORT_SYMBOL(_ZN9Interrupt6SetISREiPFvPvS0_ES0_S0_);


/// @brief Interrupt Set ISR, this will clean the isrTabs[irq]
/// @param irq irq number
/// @param method interupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::SetISR(int irq, Method method, Class* user, void* args)
{
	return SetISR(irq, union_cast<Function>(method), (void*)user, args);
}
EXPORT_SYMBOL(_ZN9Interrupt6SetISREiM5ClassFvPvEPS0_S1_);


/// @brief Interrupt append ISR
/// @param irq irq number
/// @param func interupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::AppendISR(int irq, Function func, void* user, void* args)
{
	return isrTabs[irq].Add(new Isr(irq, func, user, args));
}
EXPORT_SYMBOL(_ZN9Interrupt9AppendISREiPFvPvS0_ES0_S0_);


/// @brief Interrupt append ISR
/// @param irq irq number
/// @param method interupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return the number of the isr in isrTabs, return -1 when fail.
int Interrupt::AppendISR(int irq, Method method, Class* user, void* args)
{
	return AppendISR(irq, union_cast<Function>(method), (void*)user, args);
}
EXPORT_SYMBOL(_ZN9Interrupt9AppendISREiM5ClassFvPvEPS0_S1_);


/// @brief Interrupt remove isr
/// @param irq irq number
/// @param func interrupt function
/// @param user interrupt user
/// @param args interrupt args
/// @return Result::_OK / Result::_ERR
int Interrupt::RemoveISR(int irq, Function func, void* user, void* args)
{
	List<Isr> isrs = isrTabs[irq];

	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		if ((irq  == isr->irq ) &&
			(func == isr->func) &&
			(user == isr->user) &&
			(args == isr->args))
		{
			Result res = (Result)isrs.Remove(isr, isrs.GetNid());
			if (_OK == res) isrTabs[irq] = isrs;
			return res;
		}
	}

	return _ERR;
}
EXPORT_SYMBOL(_ZN9Interrupt9RemoveISREiPFvPvS0_ES0_S0_);


/// @brief Interrupt remove isr
/// @param irq irq number
/// @param method interrupt method
/// @param user interrupt user
/// @param args interrupt args
/// @return Result::_OK / Result::_ERR
int Interrupt::RemoveISR(int irq, Method method, Class* user, void* args)
{
	return RemoveISR(irq, union_cast<Function>(method), (void*)user, args);
}
EXPORT_SYMBOL(_ZN9Interrupt9RemoveISREiM5ClassFvPvEPS0_S1_);


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
EXPORT_SYMBOL(_ZN9Interrupt8ClearISREi);


/// @brief Interrupt handler
/// @param irq irq number
void Interrupt::Handler(int irq)
{
	List<Isr> isrs = interrupt.isrTabs[irq];
	
	if (isrs.IsEmpty())
	{
		if (++warnings[irq] >= warning_times)
		{
			debug.Error("IRQ %d no being handled correctly, system will halt on here", irq);
			while(1) {}
		}
		debug.Warn("IRQ %d has no interrupt service function", irq);
		return;
	}
	else
	{
		warnings[irq] = 0;
	}

	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		(isr->func)(isr->user, isr->args);
	}
}
