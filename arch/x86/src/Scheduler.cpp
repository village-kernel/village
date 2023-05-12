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


/// @brief Start scheduler
void Scheduler::StartScheduler()
{
	//Clear start schedule flag
	isStartSchedule = false;

	////Prepare PSP of the first task, return PSP in R0 and set PSP
	//__asm volatile("bl getTaskPSP");
	//__asm volatile("msr psp, r0");

	////Change to use PSP, set bit[1] SPSEL
	//__asm volatile("mrs r0, control");
	//__asm volatile("orr r0, r0, #2");
	//__asm volatile("msr control, r0");

	////Move to Unprivileged level, Set bit[0] nPRIV
	//__asm volatile("mrs r0, control");
	//__asm volatile("orr r0, r0, #1");
	//__asm volatile("msr control, r0");

	//Set start schedule flag
	isStartSchedule = true;

	//Set interrupt flag
	__asm volatile("sti");

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
		__asm volatile("int $31");
	}
	else
	{
		// call Supervisor exception to get Privileged access
		__asm volatile("int $30");
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
			__asm volatile("int $31");
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
	void PendSV_Handler(void)
	{
		//
		
		//Save current value of psp
		//__asm volatile("call saveTaskPSP");

		//Select next task
		thread.SelectNextTask();

		//Get its past psp value, return psp is in R0
		//__asm volatile("call getTaskPSP"); 

		//
	}


	/// @brief SysTick_Handler
	/// @param  
	void SysTick_Handler(void)
	{
		//Update systick count
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
		
	}
}
