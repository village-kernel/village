//###########################################################################
// Scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scheduler.h"
#include "Kernel.h"
#include "System.h"


/// @brief Constructor
Scheduler::Scheduler()
	:isStartSchedule(false)
{
}


/// @brief Fini constructor
Scheduler::~Scheduler()
{
}


/// @brief Scheduler initialize
void Scheduler::Initialize()
{
	//Set the PendSV interrupt handler
	Kernel::interrupt.SetISR(IRQ_PendSV, union_cast<Function>(&Scheduler::PendSVHandler), (char*)this);
	//Append the systick interrupt handler
	Kernel::interrupt.AppendISR(IRQ_Systick, union_cast<Function>(&Scheduler::SysTickHandler), (char*)this);
}


/// @brief Start scheduler
void Scheduler::Execute()
{
	//Clear start schedule flag
	isStartSchedule = false;

	//Get frist task psp
	uint32_t psp = Kernel::thread.GetTaskPSP();

	//Set frist task esp
	__asm volatile("movl %0, %%esp" : "=r"(psp));

	//Set start schedule flag
	isStartSchedule = true;

	//Set interrupt flag
	__asm volatile("sti");

	//Execute thread
	Kernel::thread.Execute();
}


/// @brief Rescheduler task
/// @param access scheduler access
void Scheduler::Rescheduler(Scheduler::Access access)
{
	if (false == isStartSchedule) return;

	// trigger PendSV directly
	__asm volatile("int $31");
}


/// @brief PendSV handler
void __attribute__((naked)) Scheduler::PendSVHandler()
{
	uint32_t psp = 0;

	//Push old task registers
	__asm volatile("pushl %ebp");
	__asm volatile("pushl %ebx");
	__asm volatile("pushl %esi");
	__asm volatile("pushl %edi");
	__asm volatile("movl %%esp, %0" : "=r"(psp));

	//Save old task psp
	Kernel::thread.SaveTaskPSP(psp);

	//Select next task
	Kernel::thread.SelectNextTask();

	//Get new task psp
	psp = Kernel::thread.GetTaskPSP();

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
void Scheduler::SysTickHandler()
{
	Rescheduler(Scheduler::Privileged);
}
