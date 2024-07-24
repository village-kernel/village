//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Hardware.h"
#include "Registers.h"


/// @brief Constructor
Exception::Exception()
{
}


/// @brief Destructor
Exception::~Exception()
{
}


/// @brief Exception Setup
void Exception::Setup()
{
	kernel->interrupt.Replace(NonMaskableInt_IRQn,     (uint32_t)&Exception::NMIHandler         );
	kernel->interrupt.Replace(HardFault_IRQn,          (uint32_t)&Exception::HardFaultHandler   );
	kernel->interrupt.Replace(MemoryManagement_IRQn,   (uint32_t)&Exception::MemManageHandler   );
	kernel->interrupt.Replace(BusFault_IRQn,           (uint32_t)&Exception::BusFaultHandler    );
	kernel->interrupt.Replace(UsageFault_IRQn,         (uint32_t)&Exception::UsageFaultHandler  );
	kernel->interrupt.Replace(DebugMonitor_IRQn,       (uint32_t)&Exception::DebugMonHandler    );
}


/// @brief Exception Exit
void Exception::Exit()
{
}


/// @brief NMIHandler
void __attribute__ ((naked)) Exception::NMIHandler()
{
	ExceptionInfo("NMI Handler");
}


/// @brief HardFaultHandler
void __attribute__ ((naked)) Exception::HardFaultHandler()
{
	ExceptionInfo("Hard Fault Handler");
}


/// @brief MemManageHandler
void __attribute__ ((naked)) Exception::MemManageHandler()
{
	ExceptionInfo("Mem Manage Handler");
}


/// @brief BusFaultHandler
void __attribute__ ((naked)) Exception::BusFaultHandler()
{
	ExceptionInfo("Bus Fault Handler");
}


/// @brief UsageFaultHandler
void __attribute__ ((naked)) Exception::UsageFaultHandler()
{
	ExceptionInfo("Usage Fault Handler");
}


/// @brief DebugMonHandler
void __attribute__ ((naked)) Exception::DebugMonHandler()
{
	ExceptionInfo("Debug Mon Handler");
}


/// @brief Exception Info
/// @param exception 
inline void Exception::ExceptionInfo(const char* exception)
{
	__asm volatile("tst lr, #4");
	__asm volatile("ite eq");
	__asm volatile("mrseq r0, msp");
	__asm volatile("mrsne r0, psp");
	__asm volatile("stmdb r0!, {r4-r11}");
	__asm volatile("mov r1, %0" : "+r"(exception));
	__asm volatile("b StackedInfo");
}


/// @brief Output stacked info
/// @param regs stack pointer
extern "C" void StackedInfo(Registers* regs, char* exception)
{
	kernel->debug.Error("r0:   0x%08lx", regs->r0);
	kernel->debug.Error("r1:   0x%08lx", regs->r1);
	kernel->debug.Error("r2:   0x%08lx", regs->r2);
	kernel->debug.Error("r3:   0x%08lx", regs->r3);
	kernel->debug.Error("r4:   0x%08lx", regs->r4);
	kernel->debug.Error("r5:   0x%08lx", regs->r5);
	kernel->debug.Error("r6:   0x%08lx", regs->r6);
	kernel->debug.Error("r7:   0x%08lx", regs->r7);
	kernel->debug.Error("r8:   0x%08lx", regs->r8);
	kernel->debug.Error("r9:   0x%08lx", regs->r9);
	kernel->debug.Error("r10:  0x%08lx", regs->r10);
	kernel->debug.Error("r11:  0x%08lx", regs->r11);
	kernel->debug.Error("r12:  0x%08lx", regs->r12);
	kernel->debug.Error("lr:   0x%08lx", regs->lr);
	kernel->debug.Error("pc:   0x%08lx", regs->pc);
	kernel->debug.Error("xpsr: 0x%08lx", regs->xpsr);
	kernel->debug.Error(exception);
	while(1) {}
}
