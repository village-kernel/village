//###########################################################################
// Scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scheduler.h"
#include "Hardware.h"


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
}


/// @brief Scheduler Exit
void ConcreteScheduler::Exit()
{
	//Append the systick interrupt handler
	kernel->interrupt.RemoveISR(SysTick_IRQn, (Method)&ConcreteScheduler::SysTickHandler, this);

	//Set the PendSV interrupt handler
	kernel->interrupt.ClearISR(PendSV_IRQn);
}


/// @brief Start scheduler
void ConcreteScheduler::Start()
{
	//Clear start schedule flag
	isStartSchedule = false;

	//Get frist task psp
	uint32_t psp = kernel->thread.GetTaskPSP();

	//Set frist task sp
	__asm volatile("mov sp, %0" : "=r"(psp));

	//Set start schedule flag
	isStartSchedule = true;

	//Execute thread
	kernel->thread.IdleTask();
}


/// @brief Rescheduler task
/// @param access scheduler access
void ConcreteScheduler::Sched()
{
	if (false == isStartSchedule) return;

	// trigger PendSV directly
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


/// @brief PendSV Handler
void __attribute__ ((naked)) ConcreteScheduler::PendSVHandler()
{
	uint32_t psp = 0;

	//Push lr regs to sp
	__asm volatile("push {lr}");
	
	//Push r4-r1 regs to sp
	__asm volatile("push {r4-r11}");

	//Get current task psp
	__asm volatile("mov %0, sp" : "=r"(psp));

	//Save old task psp
	kernel->thread.SaveTaskPSP(psp);

	//Select next task
	kernel->thread.SelectNextTask();

	//Get new task psp
	psp = kernel->thread.GetTaskPSP();

	//Set new task sp
	__asm volatile("mov sp, %0" : "=r"(psp));

	//Pop r4-r11 regs from sp
	__asm volatile("pop {r4-r11}");

	//Exit
	__asm volatile("pop {lr}");
	__asm volatile("bx lr");
}


/// @brief Systick handler
void ConcreteScheduler::SysTickHandler(void)
{
	Sched();
}
