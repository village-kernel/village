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
    //Replace the SVC interrupt handler
    kernel->interrupt.Replace(SVCall_IRQn, (uint32_t)&ConcreteScheduler::SVCHandler);

    //Replace the PendSV interrupt handler
    kernel->interrupt.Replace(PendSV_IRQn, (uint32_t)&ConcreteScheduler::PendSVHandler);

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

    //Clear the SVC interrupt handler
    kernel->interrupt.ClearISR(SVCall_IRQn);
    
    //Call Supervisor exception to get Privileged access
    __asm volatile("SVC #0");
}


/// @brief Start scheduler
void ConcreteScheduler::Start()
{
    //Output debug info
    kernel->debug.Info("Scheduler start sched!");

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

    //Move to Unprivileged level, Set bit[0] nPRIV
    __asm volatile("mrs r0, control");
    __asm volatile("orr r0, r0, #1");
    __asm volatile("msr control, r0");

    //Set start schedule flag
    isStartSchedule = true;

    //Execute thread
    kernel->thread.IdleTask();
}


/// @brief Rescheduler task
void ConcreteScheduler::Sched()
{
    if (!isStartSchedule) return;

    //Call Supervisor exception to trigger PendSV
    __asm volatile("SVC #255");
}


/// @brief Systick handler
void ConcreteScheduler::SysTickHandler(void)
{
    if (!isStartSchedule) return;

    //Trigger PendSV directly
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


/// @brief Execute task requests
/// @param sp stack pointer
void ConcreteScheduler::TaskOperator(uint32_t* sp)
{
    //Get the address of the instruction saved in PC
    uint8_t *pInstruction = (uint8_t*)(sp[6]);

    //Go back 2 bytes (16-bit opcode)
    pInstruction -= 2;

    //Get the opcode, in little endian
    uint8_t svcNumber = *pInstruction;

    //Handle svc request
    if (0 == svcNumber)
    {
        //Move to Unprivileged level, clear bit[0] nPRIV
        __asm volatile("mrs r0, control");
        __asm volatile("bic r0, r0, #1");
        __asm volatile("msr control, r0");
    }
    else if (255 == svcNumber)
    {
        //Trigger PendSV
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
}


/// @brief SVC Handler
void __attribute__ ((naked)) ConcreteScheduler::SVCHandler()
{
    __asm volatile("tst lr, 4");        // check LR to know which stack is used
    __asm volatile("ite eq");           // 2 next instructions are conditional
    __asm volatile("mrseq r0, msp");    // save MSP if bit 2 is 0
    __asm volatile("mrsne r0, psp");    // save PSP if bit 2 is 1
    __asm volatile("b _ZN17ConcreteScheduler12TaskOperatorEPm");   // pass R0 as the argument
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
