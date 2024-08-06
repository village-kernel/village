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
	//Replace the PendSV interrupt handler
	kernel->interrupt.Replace(PendSV_IRQn, (uint32_t)&ConcreteScheduler::PendSVHandler);

	//Append the systick interrupt handler
	kernel->interrupt.AppendISR(SysTick_IRQn, (Method)&ConcreteScheduler::SysTickHandler, this);
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
	//Clear start schedule flag
	isStartSchedule = false;

	//Get frist task psp
	volatile uint32_t psp = kernel->thread.GetTaskPSP();

	//Set frist task psp
	__asm volatile("msr psp, %0" : "+r"(psp));

	//Change to use PSP, set bit[1] SPSEL
	__asm volatile("mrs r0, control");
	__asm volatile("orr r0, r0, #2");
	__asm volatile("msr control, r0");

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

	//Trigger PendSV directly
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


/// @brief Systick handler
void ConcreteScheduler::SysTickHandler(void)
{
	Sched();
}


/// @brief PendSV Handler
void __attribute__ ((naked)) ConcreteScheduler::PendSVHandler()
{
	static volatile uint32_t psp = 0;

	//Push lr regs to main sp
	__asm volatile("push {lr}");

	//Get current task psp
	__asm volatile("mrs r0, psp");

	//Store r4-r11 regs
	__asm volatile("stmdb r0!, {r4-r11}");

	//Get psp value: psp = r0
	__asm volatile("mov %0, r0" : "+r"(psp));

	//Store old task psp
	kernel->thread.SaveTaskPSP(psp);

	//Select next task
	kernel->thread.SelectNextTask();

	//Get new task psp
	psp = kernel->thread.GetTaskPSP();

	//Set r0 value: r0 = psp
	__asm volatile("mov r0, %0" : "+r"(psp));

	//Restore r4-r11 regs
	__asm volatile("ldmia r0!, {r4-r11}");

	//Set new task sp
	__asm volatile("msr psp, r0");

	//Exit
	__asm volatile("pop {lr}");
	__asm volatile("bx lr");
}
