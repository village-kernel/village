//###########################################################################
// vk_scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_scheduler.h"
#include "vk_hardware.h"


/// @brief Constructor
ConcreteScheduler::ConcreteScheduler()
	:isStartSchedule(false)
{
}


/// @brief Destructor
ConcreteScheduler::~ConcreteScheduler()
{
}


/// @brief Scheduler Setup
void ConcreteScheduler::Setup()
{
	//Set the PendSV interrupt handler
	kernel->interrupt.SetISR(PendSV_IRQn, (Method)&ConcreteScheduler::PendSVHandler, this);

	//Append the systick interrupt handler
	kernel->interrupt.AppendISR(SysTick_IRQn, (Method)&ConcreteScheduler::SysTickHandler, this);

	//Output debug info
	kernel->debug.Info("Scheduler setup done!");
}


/// @brief Scheduler Exit
void ConcreteScheduler::Exit()
{
	//Remove the systick interrupt handler
	kernel->interrupt.RemoveISR(SysTick_IRQn, (Method)&ConcreteScheduler::SysTickHandler, this);

	//Clear the PendSV interrupt handler
	kernel->interrupt.ClearISR(PendSV_IRQn);
}


/// @brief Start scheduler
void ConcreteScheduler::Start()
{
	//Output debug info
	kernel->debug.Info("Scheduler start sched!");

	//Clear start schedule flag
	isStartSchedule = false;

	//Get frist task psp
	uint32_t psp = kernel->thread.GetTaskPSP();

	//Set frist task esp
	__asm volatile("movl %0, %%esp" : "=r"(psp));

	//Set start schedule flag
	isStartSchedule = true;

	//Set interrupt flag
	__asm volatile("sti");

	//Execute thread idle task
	kernel->thread.IdleTask();
}


/// @brief Rescheduler task
/// @param access scheduler access
void ConcreteScheduler::Sched()
{
	if (false == isStartSchedule) return;

	//Trigger PendSV directly
	__asm volatile("int $31");
}


/// @brief SysTick handler
void ConcreteScheduler::SysTickHandler()
{
	Sched();
}


/// @brief PendSV handler
void __attribute__((naked)) ConcreteScheduler::PendSVHandler()
{
	uint32_t psp = 0;

	//Push old task registers
	__asm volatile("pushl %ebp");
	__asm volatile("pushl %ebx");
	__asm volatile("pushl %esi");
	__asm volatile("pushl %edi");
	__asm volatile("movl %%esp, %0" : "=r"(psp));

	//Save old task psp
	kernel->thread.SaveTaskPSP(psp);

	//Select next task
	kernel->thread.SelectNextTask();

	//Get new task psp
	psp = kernel->thread.GetTaskPSP();

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
