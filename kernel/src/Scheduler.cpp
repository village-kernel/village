//###########################################################################
// Scheduler.cpp
// Definitions of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Scheduler.h"
#include "Thread.h"
#include "System.h"


///Initialize static members
bool Scheduler::isStartSchedule = false;


///Constructor
Scheduler::Scheduler()
{
}


///Start scheduler
void Scheduler::StartScheduler()
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

	//Get the handler of the first task by tracing back from PSP which is at R4 slot
	void (*Handler)() = (void (*)())((uint32_t*)(Thread::GetTaskHandler()));

	//Execute the handler
	Handler();
}


///Rescheduler task
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
		__ASM("SVC #255");
	}
}


///Execute task requests
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


///Interrupt handlers
extern "C" 
{
	//Call thread save task psp in c function
	void saveTaskPSP(uint32_t psp)
	{
		Thread::SaveTaskPSP(psp);
	}

	//Call thread get task psp in c function
	uint32_t getTaskPSP()
	{
		return Thread::GetTaskPSP();
	}

	///PendSV_Handler
	__attribute__ ((naked)) void PendSV_Handler(void)
	{
		//Save LR back to main, must do this firstly
		__ASM("push {lr}");

		//Gets the current psp
		__ASM("mrs r0, psp");

		//Save R4 to R11 to psp frame stack
		__ASM("stmdb r0!, {r4-r11}");

		//Save current value of psp
		__ASM("bl saveTaskPSP");

		//Select next task
		Thread::SelectNextTask();

		//Get its past psp value, return psp is in R0
		__ASM("bl getTaskPSP"); 

		//Retrieve R4-R11 from psp frame stack
		__ASM("ldmia r0!, {r4-r11}");
		
		//Update psp
		__ASM("msr psp, r0");

		//Exit
		__ASM("pop {lr}");
		__ASM("bx lr");
	}

	///Systick handler
	void SysTick_Handler(void)
	{
		System::SysTickCounter();
		Scheduler::Rescheduler(Scheduler::Privileged);
	}

	//Call scheduler task operator in c function
	void taskOperator(uint32_t* sp)
	{
		Scheduler::TaskOperator(sp);
	}

	///SVC_Handler
	__attribute__ ((naked)) void SVC_Handler(void)
	{
		__ASM("tst lr, 4"); // check LR to know which stack is used
		__ASM("ite eq"); // 2 next instructions are conditional
		__ASM("mrseq r0, msp"); // save MSP if bit 2 is 0
		__ASM("mrsne r0, psp"); // save PSP if bit 2 is 1
		__ASM("b taskOperator"); // pass R0 as the argument
	}
	
	//Call hard_fault_handler_c in c function
	void hard_fault_handler_c(unsigned int * hardfault_args)
	{
		volatile uint32_t stacked_r0 = ((uint32_t)hardfault_args[0]);
		volatile uint32_t stacked_r1 = ((uint32_t)hardfault_args[1]);
		volatile uint32_t stacked_r2 = ((uint32_t)hardfault_args[2]);
		volatile uint32_t stacked_r3 = ((uint32_t)hardfault_args[3]);

		volatile uint32_t stacked_r12 = ((uint32_t)hardfault_args[4]);
		volatile uint32_t stacked_lr  = ((uint32_t)hardfault_args[5]);
		volatile uint32_t stacked_pc  = ((uint32_t)hardfault_args[6]);
		volatile uint32_t stacked_psr = ((uint32_t)hardfault_args[7]);

		printf("Hard_Fault_Handler: \r\n");
		printf("r0:   0x%08lx\r\n", stacked_r0);
		printf("r1:   0x%08lx\r\n", stacked_r1);
		printf("r2:   0x%08lx\r\n", stacked_r2);
		printf("r3:   0x%08lx\r\n", stacked_r3);
		printf("r12:  0x%08lx\r\n", stacked_r12);
		printf("lr:   0x%08lx\r\n", stacked_lr);
		printf("pc:   0x%08lx\r\n", stacked_pc);
		printf("xpsr: 0x%08lx\r\n", stacked_psr);

		while (1);
	}
	
	///HardFault_Handler
	void HardFault_Handler(void)
	{
		__ASM("tst lr, #4"); // check LR to know which stack is used
		__ASM("ite eq"); // 2 next instructions are conditional
		__ASM("mrseq r0, msp"); // save MSP if bit 2 is 0
		__ASM("mrsne r0, psp"); // save PSP if bit 2 is 1
		__ASM("b hard_fault_handler_c"); // pass R0 as the argument
	}
}
