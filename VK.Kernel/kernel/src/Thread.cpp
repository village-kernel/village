//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Thread.h"

#include "Gpo.h"

struct TaskStack {
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r12;
	unsigned int lr;
	unsigned int pc;
	unsigned int xpsr;

	TaskStack():
		r4(0),
		r5(0),
		r6(0),
		r7(0),
		r8(0),
		r9(0),
		r10(0),
		r11(0),
		r0(0),
		r1(0),
		r2(0),
		r3(0),
		r12(0),
		lr(0),
		pc(0),
		xpsr(0)
	{}
};


void Task0(void)
{
	// Gpo led;
	
	// led.Initialize(Gpio::_ChE, 5, Gpio::_Low);

	// while(1) 
	// {
	// 	led.Set();
	// 	System::DelayMs(500);
	// 	led.Clear();
	// 	System::DelayMs(500);
	// }

	while(1) {
		printf("1111\n");
	}
}

void Task1(void)
{
	// Gpo led;
	
	// led.Initialize(Gpio::_ChA, 8, Gpio::_Low);

	// while (1)
	// {
	// 	led.Set();
	// 	System::DelayMs(500);
	// 	led.Clear();
	// 	System::DelayMs(500);
	// }

	while(1) {
		printf("2222\n");
	}
}


class Task
{
private:
	static const unsigned int task_stack = 0x20000000;
	static const unsigned int task_number_size = 16;
	static const unsigned int task_stack_szie = 1024;
	static const unsigned int main_stack = task_stack + (128 * 1024);
public:
	unsigned int storedIndex;
   	unsigned int taskIndex;
	unsigned int tasksPSP[task_number_size] = { 0 };
	
	///Constructor
	Task()
		:storedIndex(0),
		taskIndex(0)
    {
    }

	///Create new task
	void CreateTask(void (*task)())
	{
		if(storedIndex >= task_number_size) return;

		uint32_t *newTaskPSP = (uint32_t*)(main_stack - (storedIndex + 1) * task_stack_szie);

		// fill dummy stack frame
		*(--newTaskPSP) = 0x01000000u; // Dummy xPSR, just enable Thumb State bit;
		*(--newTaskPSP) = (uint32_t)task; // PC
		*(--newTaskPSP) = 0xFFFFFFFDu; // LR with EXC_RETURN to return to Thread using PSP
		*(--newTaskPSP) = 0x0; // Dummy R12
		*(--newTaskPSP) = 0x0; // Dummy R3
		*(--newTaskPSP) = 0x0; // Dummy R2
		*(--newTaskPSP) = 0x0; // Dummy R1
		*(--newTaskPSP) = 0x0; // Dummy R0
		*(--newTaskPSP) = 0x0; // Dummy R11
		*(--newTaskPSP) = 0x0; // Dummy R10
		*(--newTaskPSP) = 0x0; // Dummy R9
		*(--newTaskPSP) = 0x0; // Dummy R8
		*(--newTaskPSP) = 0x0; // Dummy R7
		*(--newTaskPSP) = 0x0; // Dummy R6
		*(--newTaskPSP) = 0x0; // Dummy R5
		*(--newTaskPSP) = 0x0; // Dummy R4

		tasksPSP[storedIndex++] = (uint32_t)newTaskPSP;
	}

	///Save task PSP
	void SaveTaskPSP(uint32_t psp)
	{
		tasksPSP[taskIndex] = psp;
	}

	///Get current task psp
	uint32_t GetTaskPSP()
	{
		return tasksPSP[taskIndex];
	}

    /// Select next task
    void SelectNextTask()
    {
		if (++taskIndex >= storedIndex) taskIndex = 0;
    }
};

Task *task = new Task();

extern "C" 
{
	void saveTaskPSP(uint32_t psp)
	{
		task->SaveTaskPSP(psp);
	}

	uint32_t getTaskPSP()
	{
		return task->GetTaskPSP();
	}

	void SysTick_Handler(void)
	{
		//Save LR back to main, must do this firstly
		__ASM("push {lr}");

		//Gets the current msp
		__ASM("mrs r0, psp");

		//Save R4 to R11 to msp frame stack
		__ASM("stmdb r0!, {r4-r11}");

		//Save current value of msp
		__ASM("bl saveTaskPSP");

		//Select next task
		task->SelectNextTask();

		//Get its past PSP value, return PSP is in R0
		__ASM("bl getTaskPSP"); 

		//Retrieve R4-R11 from msp frame stack
		__ASM("ldmia r0!, {r4-r11}");
		
		//Update msp
		__ASM("msr psp, r0");

		//Exit
		__ASM("pop {lr}");
		__ASM("bx lr");
	}

	void StartScheduler()
	{
		//Create tasks
		task->CreateTask(Task0);
		task->CreateTask(Task1);

		//Prepare PSP of the first task, return PSP in R0 and set PSP
		__ASM("bl getTaskPSP");
		__ASM("msr psp, r0"); 

		//Change to use PSP, set bit[1] SPSEL
		__ASM("mrs r0, control");
		__ASM("orr r0, r0, #2");
		__ASM("msr control, r0");

		//Enable systick interrupt
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
		
		//Set systick reload value
		SysTick->LOAD = 210000;
		
		//Clear systick current value
		SysTick->VAL = 0;
		
		//Enable systick
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

		//Move to Unprivileged level, Set bit[0] nPRIV
		__ASM("mrs r0, control");
		__ASM("orr r0, r0, #1");
		__ASM("msr control, r0");
	
		//Get the handler of the first task by tracing back from PSP which is at R4 slot
		void (*Handler)() = (void (*)())((uint32_t*)(((TaskStack*)task->GetTaskPSP())->pc));

		//Execute the handler
		Handler();
	}
}
