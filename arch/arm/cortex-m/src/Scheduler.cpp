//###########################################################################
// Scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scheduler.h"
#include "Thread.h"
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


/// @brief Singleton Instance
/// @return Scheduler instance
Scheduler& Scheduler::Instance()
{
	static Scheduler instance;
	return instance;
}


/// @brief Definitions scheduler
Scheduler& scheduler = Scheduler::Instance();


/// @brief Scheduler initialize
void Scheduler::Initialize()
{

}


/// @brief Start scheduler
void Scheduler::Execute()
{
	//Clear start schedule flag
	isStartSchedule = false;

	//Prepare PSP of the first task, return PSP in R0 and set PSP
	__ASM("bl getTaskPSP");
	__ASM("msr psp, r0");

	//Change to use PSP, set bit[1] SPSEL
	__ASM("mrs r0, control");
	__ASM("orr r0, r0, #2");
	__ASM("msr control, r0");

	//Move to Unprivileged level, Set bit[0] nPRIV
	__ASM("mrs r0, control");
	__ASM("orr r0, r0, #1");
	__ASM("msr control, r0");

	//Set start schedule flag
	isStartSchedule = true;

	//Execute thread
	thread.Execute();
}


/// @brief Rescheduler task
/// @param access scheduler access
void Scheduler::Rescheduler(Scheduler::Access access)
{
	if (false == isStartSchedule) return;

	if (Access::Privileged == access)
	{
		// trigger PendSV directly
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}
	else
	{
		// call Supervisor exception to get Privileged access
		__asm volatile("SVC #255");
	}
}


/// @brief Execute task requests
/// @param sp stack pointer
void Scheduler::TaskOperator(uint32_t* sp)
{
	//Get the address of the instruction saved in PC
	uint8_t *pInstruction = (uint8_t*)(sp[6]);

	//Go back 2 bytes (16-bit opcode)
	pInstruction -= 2;

	//Get the opcode, in little endian
	uint8_t svcNumber = *pInstruction;

	switch(svcNumber)
	{
		case 0xFF:
			//Trigger PendSV
			SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
			break;
		default:
			break;
	}
}


/// @brief Interrupt handlers
extern "C" 
{
	/// @brief Call thread save task psp in c function
	/// @param psp process stack pointer
	void saveTaskPSP(uint32_t psp)
	{
		thread.SaveTaskPSP(psp);
	}


	/// @brief Call thread get task psp in c function
	/// @return process stack pointer
	uint32_t getTaskPSP()
	{
		return thread.GetTaskPSP();
	}


	/// @brief PendSV_Handler
	/// @param  
	__attribute__ ((naked)) void PendSV_Handler(void)
	{
		//Save LR back to main, must do this firstly
		__asm volatile("push {lr}");

		//Gets the current psp
		__asm volatile("mrs r0, psp");

		//Save R4 to R11 to psp frame stack
		__asm volatile("stmdb r0!, {r4-r11}");

		//Save current value of psp
		__asm volatile("bl saveTaskPSP");

		//Select next task
		thread.SelectNextTask();

		//Get its past psp value, return psp is in R0
		__asm volatile("bl getTaskPSP"); 

		//Retrieve R4-R11 from psp frame stack
		__asm volatile("ldmia r0!, {r4-r11}");
		
		//Update psp
		__asm volatile("msr psp, r0");

		//Exit
		__asm volatile("pop {lr}");
		__asm volatile("bx lr");
	}


	/// @brief Systick handler
	/// @param  
	void SysTick_Handler(void)
	{
		System::SysTickCounter();
		scheduler.Rescheduler(Scheduler::Privileged);
	}


	/// @brief Call scheduler task operator in c function
	/// @param sp stack pointer
	void taskOperator(uint32_t* sp)
	{
		scheduler.TaskOperator(sp);
	}


	/// @brief SVC_Handler
	/// @param  
	__attribute__ ((naked)) void SVC_Handler(void)
	{
		__asm volatile("tst lr, 4");        // check LR to know which stack is used
		__asm volatile("ite eq");           // 2 next instructions are conditional
		__asm volatile("mrseq r0, msp");    // save MSP if bit 2 is 0
		__asm volatile("mrsne r0, psp");    // save PSP if bit 2 is 1
		__asm volatile("b taskOperator");   // pass R0 as the argument
	}
}
