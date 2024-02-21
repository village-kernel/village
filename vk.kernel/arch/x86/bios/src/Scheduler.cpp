//###########################################################################
// Scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scheduler.h"
#include "Interrupt.h"
#include "Thread.h"
#include "Kernel.h"
#include "System.h"


/// @brief ConcreteScheduler
class ConcreteScheduler : public Scheduler
{
private:
	//Members
	Interrupt* interrupt;
	bool       isStartSchedule;
public:
	/// @brief Constructor
	ConcreteScheduler()
		:interrupt(NULL),
		isStartSchedule(false)
	{
	}


	/// @brief Destructor
	~ConcreteScheduler()
	{
	}


	/// @brief Scheduler Setup
	void Setup()
	{
		//Gets the interrupt pointer
		interrupt = (Interrupt*)kernel->modular->GetModule(ModuleID::_interrupt);

		//Set the PendSV interrupt handler
		interrupt->SetISR(IRQ_PendSV, (Method)&ConcreteScheduler::PendSVHandler, this);

		//Append the systick interrupt handler
		interrupt->AppendISR(IRQ_Systick, (Method)&ConcreteScheduler::SysTickHandler, this);
	}


	/// @brief Exit
	void Exit()
	{

	}


	/// @brief Start scheduler
	void StartScheduler()
	{
		//Clear start schedule flag
		isStartSchedule = false;

		//Get frist task psp
		uint32_t psp = kernel->thread->GetTaskPSP();

		//Set frist task esp
		__asm volatile("movl %0, %%esp" : "=r"(psp));

		//Set start schedule flag
		isStartSchedule = true;

		//Set interrupt flag
		__asm volatile("sti");

		//Execute thread idle task
		kernel->thread->IdleTask();
	}


	/// @brief Rescheduler task
	/// @param access scheduler access
	void Rescheduler(Scheduler::Access access)
	{
		if (false == isStartSchedule) return;

		//Trigger PendSV directly
		__asm volatile("int $31");
	}
private:
	/// @brief PendSV handler
	void __attribute__((naked)) PendSVHandler()
	{
		uint32_t psp = 0;

		//Push old task registers
		__asm volatile("pushl %ebp");
		__asm volatile("pushl %ebx");
		__asm volatile("pushl %esi");
		__asm volatile("pushl %edi");
		__asm volatile("movl %%esp, %0" : "=r"(psp));

		//Save old task psp
		kernel->thread->SaveTaskPSP(psp);

		//Select next task
		kernel->thread->SelectNextTask();

		//Get new task psp
		psp = kernel->thread->GetTaskPSP();

		//Set new task esp
		__asm volatile("movl %0, %%esp" : "=r"(psp));

		//Pop new task registers
		__asm volatile("popl %edi");
		__asm volatile("popl %esi");
		__asm volatile("popl %ebx");
		__asm volatile("popl %ebp");
		__asm volatile("sti");
		__asm volatile("ret");
	}


	/// @brief SysTick handler
	void SysTickHandler()
	{
		Rescheduler(Scheduler::Privileged);
	}
};


///Register module
REGISTER_MODULE(ConcreteScheduler, ModuleID::_scheduler, scheduler);
