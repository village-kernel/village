//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"

unsigned int Thread::storedIndex = 0;
unsigned int Thread::taskIndex = 0;
unsigned int Thread::sysTicks = 0;
Thread::Task Thread::tasks[Thread::task_number_size];

///Constructor
Thread::Thread()
{
}


///Create new task
void Thread::CreateTask(void (*handler)())
{
	//Check
	if(storedIndex >= task_number_size) return;

	//Init idle if it is not found
	if (handler != &IdleTask)
	{
		if (tasks[0].handler != IdleTask)
		{
			CreateTask(IdleTask);
		}
	}

	//Calculate new task psp address
	uint32_t *psp = (uint32_t*)(end_stack - (storedIndex + 1) * task_stack_szie);

	//Fill dummy stack frame
	*(--psp) = 0x01000000u; // Dummy xPSR, just enable Thumb State bit;
	*(--psp) = (uint32_t)handler; // PC
	*(--psp) = 0xFFFFFFFDu; // LR with EXC_RETURN to return to Thread using PSP
	*(--psp) = 0x0; // Dummy R12
	*(--psp) = 0x0; // Dummy R3
	*(--psp) = 0x0; // Dummy R2
	*(--psp) = 0x0; // Dummy R1
	*(--psp) = 0x0; // Dummy R0
	*(--psp) = 0x0; // Dummy R11
	*(--psp) = 0x0; // Dummy R10
	*(--psp) = 0x0; // Dummy R9
	*(--psp) = 0x0; // Dummy R8
	*(--psp) = 0x0; // Dummy R7
	*(--psp) = 0x0; // Dummy R6
	*(--psp) = 0x0; // Dummy R5
	*(--psp) = 0x0; // Dummy R4

	//Stored task info
  tasks[storedIndex].psp = (uint32_t)psp;
	tasks[storedIndex].handler = handler;
	tasks[storedIndex].state = TaskState::Running;
	storedIndex++;
}


///Save task PSP
void Thread::SaveTaskPSP(uint32_t psp)
{
	tasks[taskIndex].psp = psp;
}


///Get current task psp
uint32_t Thread::GetTaskPSP()
{
	return tasks[taskIndex].psp;
}


///Get currenttask handler
uint32_t Thread::GetTaskHandler()
{
	return (uint32_t)tasks[taskIndex].handler;
}


///Select next task
void Thread::SelectNextTask()
{
	//Check all task state
	for(uint32_t i = 0; i < storedIndex; i++) 
	{
		if(tasks[i].state == TaskState::Blocked) 
		{
			if(sysTicks >= tasks[i].waitToTick)
			{
				tasks[i].state = TaskState::Running;
			}
		}
	}

	//Round-Robin scheduler
	while (1)
	{
		if (++taskIndex >= storedIndex) taskIndex = 0;

		if(tasks[taskIndex].state == TaskState::Running) break;
	}
}


///Rescheduler task
void Thread::Rescheduler(Thread::Access access)
{
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


///Thread sleep
void Thread::Sleep(uint32_t ticks)
{
	if(taskIndex)
	{
		tasks[taskIndex].state = TaskState::Blocked;
		tasks[taskIndex].waitToTick = sysTicks + ticks;
		Rescheduler(Access::Unprivileged);
	}
}


///Systick count
void Thread::SystickCount()
{
	sysTicks++;
	Rescheduler(Access::Privileged);
}


///Execute task requests
void Thread::TaskOperator(uint32_t* sp)
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

extern "C" 
{

#include "Gpo.h"

	void IdleTask(void)
	{
		while(1)
		{
			__ASM("NOP");
		}
	}

	void Task0(void)
	{
		Gpo led;

		led.Initialize(Gpio::_ChE, 5, Gpio::_Low);

		while(1) 
		{
			led.Set();
			Thread::Sleep(500);
			led.Clear();
			Thread::Sleep(500);
		}
	}

	void Task1(void)
	{
		Gpo led;

		led.Initialize(Gpio::_ChA, 8, Gpio::_Low);

		while (1)
		{
			led.Set();
			Thread::Sleep(500);
			led.Clear();
			Thread::Sleep(500);
		}
	}

	void saveTaskPSP(uint32_t psp)
	{
		Thread::SaveTaskPSP(psp);
	}

	uint32_t getTaskPSP()
	{
		return Thread::GetTaskPSP();
	}

	void SysTick_Handler(void)
	{
		Thread::SystickCount();
	}

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

	__attribute__ ((naked)) void SVC_Handler(void)
	{
		__ASM("TST LR, 4"); // check LR to know which stack is used
		__ASM("ITE EQ"); // 2 next instructions are conditional
		__ASM("MRSEQ R0, MSP"); // save MSP if bit 2 is 0
		__ASM("MRSNE R0, PSP"); // save PSP if bit 2 is 1
		__ASM("B SVC_Handler_Main"); // pass R0 as the argument
	}

	void SVC_Handler_Main(uint32_t* sp)
	{
		Thread::TaskOperator(sp);
	}

	void ConfigSysTick()
	{
		//Enable systick interrupt
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
		
		//Set systick reload value
		SysTick->LOAD = 21000;
		
		//Clear systick current value
		SysTick->VAL = 0;
		
		//Enable systick
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}

	void StartScheduler()
	{
		//Create tasks
		Thread::CreateTask(Task0);
		Thread::CreateTask(Task1);

		//Prepare PSP of the first task, return PSP in R0 and set PSP
		__ASM("bl getTaskPSP");
		__ASM("msr psp, r0");

		//Change to use PSP, set bit[1] SPSEL
		__ASM("mrs r0, control");
		__ASM("orr r0, r0, #2");
		__ASM("msr control, r0");

		//Configure system tick
		ConfigSysTick();

		//Move to Unprivileged level, Set bit[0] nPRIV
		__ASM("mrs r0, control");
		__ASM("orr r0, r0, #1");
		__ASM("msr control, r0");
	
		//Get the handler of the first task by tracing back from PSP which is at R4 slot
		void (*Handler)() = (void (*)())((uint32_t*)(Thread::GetTaskHandler()));

		//Execute the handler
		Handler();
	}
}
