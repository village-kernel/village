//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Interrupt.h"
#include "Hardware.h"
#include "Registers.h"
#include "Kernel.h"


/// @brief Exception Setup
void Exception::Setup()
{
	//Symbol defined in the linker script
	extern void (*_svector [])(void);
	extern void (*_evector [])(void);

	//Calculate the size of isr vector
	uint32_t count = _evector - _svector;

	//Set interrupt handler
	for (uint32_t i = 1; i < count; i++)
	{
		//The first func is _start(), we don't need
		Install(i - 1, (uint32_t)_svector[i]);
	}

	//Install handlers
	InstallHandlers();

	//Remap the PIC
	RemapPIC();

	//Set IDT
	SetIdt();
}


/// @brief Exception Exit
void Exception::Exit()
{
	UninstallHandlers();
}


/// @brief Install idt gate
/// @param irq 
/// @param handler 
void Exception::Install(int irq, uint32_t handler)
{
	idt[irq].lowOffset = low_16(handler);
	idt[irq].highOffset = high_16(handler);
	idt[irq].sel = kernel_code_segment;
	idt[irq].flags = 0x8E; 
}


/// @brief Get pic irq reg
/// @param ocw3 OCW3 to PIC CMD to get the register values PIC2 is chained, 
///             and represents IRQs 8-15. PIC1 is IRQs 0-7, with 2 being the chain
/// @return irq reg value
uint16_t Exception::GetPicIrqReg(int ocw3)
{
	PortByteOut(PIC1_CMD, ocw3);
	PortByteOut(PIC2_CMD, ocw3);
	return (PortByteIn(PIC2_CMD) << 8) | PortByteIn(PIC1_CMD);
}


/// @brief Get PIC irr value
/// @return Returns the combined value of the cascaded PICs irq request register 
uint16_t Exception::GetPicIrr()
{
	return GetPicIrqReg(PIC_READ_IRR);
}


/// @brief Get PIC isr value
/// @return Returns the combined value of the cascaded PICs in-service register
uint16_t Exception::GetPicIsr()
{
	return GetPicIrqReg(PIC_READ_ISR);
}


/// @brief Set idt
void Exception::SetIdt()
{
	idtReg.base = (uint32_t)&idt;
	idtReg.limit = idt_entires * sizeof(IdtGate) - 1;
	__asm volatile("lidtl (%0)" : : "r" (&idtReg));
}


/// @brief Remap the PIC
void Exception::RemapPIC()
{
	//Save masks
	uint8_t a1 = PortByteIn(PIC1_DATA);
	uint8_t a2 = PortByteIn(PIC2_DATA);

	//starts the initialization sequence (in cascade mode)
	PortByteOut(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
	PortByteOut(PIC2_CMD, ICW1_INIT | ICW1_ICW4);

	//ICW2: Master PIC vector offset
	PortByteOut(PIC1_DATA, 0x20);
	//ICW2: Slave PIC vector offset
	PortByteOut(PIC2_DATA, 0x28);
	
	//ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	PortByteOut(PIC1_DATA, 0x04);
	//ICW3: tell Slave PIC its cascade identity (0000 0010)
	PortByteOut(PIC2_DATA, 0x02);

	//ICW4: have the PICs use 8086 mode (and not 8080 mode)
	PortByteOut(PIC1_DATA, ICW4_8086);  
	PortByteOut(PIC2_DATA, ICW4_8086);

	//Restore saved masks
	PortByteOut(PIC1_DATA, a1);
	PortByteOut(PIC2_DATA, a2);
}


/// @brief Exception install handlers
void Exception::InstallHandlers()
{
	kernel->interrupt.AppendISR(Division_By_Zero_IRQn,            (Method)&Exception::DivisionByZeroHandler,            this);
	kernel->interrupt.AppendISR(Debug_IRQn,                       (Method)&Exception::DebugHandler,                     this);
	kernel->interrupt.AppendISR(Non_Maskable_Interrupt_IRQn,      (Method)&Exception::NonMaskableInterruptHandler,      this);
	kernel->interrupt.AppendISR(Breakpoint_IRQn,                  (Method)&Exception::BreakpointHandler,                this);
	kernel->interrupt.AppendISR(Into_Detected_Overflow_IRQn,      (Method)&Exception::IntoDetectedOverflowHandler,      this);
	kernel->interrupt.AppendISR(Out_Of_Bounds_IRQn,               (Method)&Exception::OutOfBoundsHandler,               this);
	kernel->interrupt.AppendISR(Invalid_Opcode_IRQn,              (Method)&Exception::InvalidOpcodeHandler,             this);
	kernel->interrupt.AppendISR(No_Coprocessor_IRQn,              (Method)&Exception::NoCoprocessorHandler,             this);
	kernel->interrupt.AppendISR(Doule_Fault_IRQn,                 (Method)&Exception::DouleFaultHandler,                this);
	kernel->interrupt.AppendISR(Coprocessor_Segment_Overrun_IRQn, (Method)&Exception::CoprocessorSegmentOverrunHandler, this);
	kernel->interrupt.AppendISR(Bad_TSS_IRQn,                     (Method)&Exception::BadTSSHandler,                    this);
	kernel->interrupt.AppendISR(Segment_Not_Present_IRQn,         (Method)&Exception::SegmentNotPresentHandler,         this);
	kernel->interrupt.AppendISR(Stack_Fault_IRQn,                 (Method)&Exception::StackFaultHandler,                this);
	kernel->interrupt.AppendISR(General_Protection_Fault_IRQn,    (Method)&Exception::GeneralProtectionFaultHandler,    this);
	kernel->interrupt.AppendISR(Page_Fault_IRQn,                  (Method)&Exception::PageFaultHandler,                 this);
	kernel->interrupt.AppendISR(Unknown_Interrupt_IRQn,           (Method)&Exception::UnknownInterruptHandler,          this);
	kernel->interrupt.AppendISR(Coprocessor_Fault_IRQn,           (Method)&Exception::CoprocessorFaultHandler,          this);
	kernel->interrupt.AppendISR(Alignment_Check_IRQn,             (Method)&Exception::AlignmentCheckHandler,            this);
	kernel->interrupt.AppendISR(Machine_Check_IRQn,               (Method)&Exception::MachineCheckHandler,              this);
}


/// @brief Exception uninstall handlers
void Exception::UninstallHandlers()
{
	kernel->interrupt.RemoveISR(Division_By_Zero_IRQn,            (Method)&Exception::DivisionByZeroHandler,            this);
	kernel->interrupt.RemoveISR(Debug_IRQn,                       (Method)&Exception::DebugHandler,                     this);
	kernel->interrupt.RemoveISR(Non_Maskable_Interrupt_IRQn,      (Method)&Exception::NonMaskableInterruptHandler,      this);
	kernel->interrupt.RemoveISR(Breakpoint_IRQn,                  (Method)&Exception::BreakpointHandler,                this);
	kernel->interrupt.RemoveISR(Into_Detected_Overflow_IRQn,      (Method)&Exception::IntoDetectedOverflowHandler,      this);
	kernel->interrupt.RemoveISR(Out_Of_Bounds_IRQn,               (Method)&Exception::OutOfBoundsHandler,               this);
	kernel->interrupt.RemoveISR(Invalid_Opcode_IRQn,              (Method)&Exception::InvalidOpcodeHandler,             this);
	kernel->interrupt.RemoveISR(No_Coprocessor_IRQn,              (Method)&Exception::NoCoprocessorHandler,             this);
	kernel->interrupt.RemoveISR(Doule_Fault_IRQn,                 (Method)&Exception::DouleFaultHandler,                this);
	kernel->interrupt.RemoveISR(Coprocessor_Segment_Overrun_IRQn, (Method)&Exception::CoprocessorSegmentOverrunHandler, this);
	kernel->interrupt.RemoveISR(Bad_TSS_IRQn,                     (Method)&Exception::BadTSSHandler,                    this);
	kernel->interrupt.RemoveISR(Segment_Not_Present_IRQn,         (Method)&Exception::SegmentNotPresentHandler,         this);
	kernel->interrupt.RemoveISR(Stack_Fault_IRQn,                 (Method)&Exception::StackFaultHandler,                this);
	kernel->interrupt.RemoveISR(General_Protection_Fault_IRQn,    (Method)&Exception::GeneralProtectionFaultHandler,    this);
	kernel->interrupt.RemoveISR(Page_Fault_IRQn,                  (Method)&Exception::PageFaultHandler,                 this);
	kernel->interrupt.RemoveISR(Unknown_Interrupt_IRQn,           (Method)&Exception::UnknownInterruptHandler,          this);
	kernel->interrupt.RemoveISR(Coprocessor_Fault_IRQn,           (Method)&Exception::CoprocessorFaultHandler,          this);
	kernel->interrupt.RemoveISR(Alignment_Check_IRQn,             (Method)&Exception::AlignmentCheckHandler,            this);
	kernel->interrupt.RemoveISR(Machine_Check_IRQn,               (Method)&Exception::MachineCheckHandler,              this);
}


/// @brief DivisionByZeroHandler
void Exception::DivisionByZeroHandler()
{
	kernel->debug.Error("Division By Zero");
	while(1) {}
}


/// @brief DebugHandler
void Exception::DebugHandler()
{
	kernel->debug.Error("Debug");
	while(1) {}
}


/// @brief NonMaskableInterruptHandler
void Exception::NonMaskableInterruptHandler()
{
	kernel->debug.Error("Non Maskable Interrupt");
	while(1) {}
}


/// @brief BreakpointHandler
void Exception::BreakpointHandler()
{
	kernel->debug.Error("Breakpoint");
	while(1) {}
}


/// @brief IntoDetectedOverflowHandler
void Exception::IntoDetectedOverflowHandler()
{
	kernel->debug.Error("Into Detected Overflow");
	while(1) {}
}


/// @brief OutOfBoundsHandler
void Exception::OutOfBoundsHandler()
{
	kernel->debug.Error("Out Of Bounds");
	while(1) {}
}


/// @brief InvalidOpcodeHandler
void Exception::InvalidOpcodeHandler()
{
	kernel->debug.Error("Invalid Opcode");
	while(1) {}
}


/// @brief NoCoprocessorHandler
void Exception::NoCoprocessorHandler()
{
	kernel->debug.Error("No Coprocessor");
	while(1) {}
}


/// @brief DouleFaultHandler
void Exception::DouleFaultHandler()
{
	kernel->debug.Error("Doule Fault");
	while(1) {}
}


/// @brief CoprocessorSegmentOverrunHandler
void Exception::CoprocessorSegmentOverrunHandler()
{
	kernel->debug.Error("Coprocessor Segment Overrun");
	while(1) {}
}


/// @brief BadTSSHandler
void Exception::BadTSSHandler()
{
	kernel->debug.Error("Bad TSS");
	while(1) {}
}


/// @brief SegmentNotPresentHandler
void Exception::SegmentNotPresentHandler()
{
	kernel->debug.Error("Segment Not Present");
	while(1) {}
}


/// @brief StackFaultHandler
void Exception::StackFaultHandler()
{
	kernel->debug.Error("Stack Fault");
	while(1) {}
}


/// @brief GeneralProtectionFaultHandler
void Exception::GeneralProtectionFaultHandler()
{
	kernel->debug.Error("General Protection Fault");
	while(1) {}
}


/// @brief PageFaultHandler
void Exception::PageFaultHandler()
{
	kernel->debug.Error("Page Fault");
	while(1) {}
}


/// @brief UnknownInterruptHandler
void Exception::UnknownInterruptHandler()
{
	kernel->debug.Error("Unknown Interrupt");
	while(1) {}
}


/// @brief CoprocessorFaultHandler
void Exception::CoprocessorFaultHandler()
{
	kernel->debug.Error("Coprocessor Fault");
	while(1) {}
}


/// @brief AlignmentCheckHandler
void Exception::AlignmentCheckHandler()
{
	kernel->debug.Error("Alignment Check");
	while(1) {}
}


/// @brief MachineCheckHandler
void Exception::MachineCheckHandler()
{
	kernel->debug.Error("Machine Check");
	while(1) {}
}


/// @brief Output stacked info
/// @param regs stack pointer
extern "C" void StackedInfo(Registers* regs)
{
	kernel->debug.Error("Hard_Fault_Handler:");

	kernel->debug.Error("irq:    0x%08lx", regs->irq);
	kernel->debug.Error("err:    0x%08lx", regs->err);
	kernel->debug.Error("psp:    0x%08lx", regs->psp);

	kernel->debug.Error("CPU:");
	kernel->debug.Error("eax:    0x%08lx", regs->eax);
	kernel->debug.Error("ecx:    0x%08lx", regs->ecx);
	kernel->debug.Error("edx:    0x%08lx", regs->edx);
	kernel->debug.Error("ebx:    0x%08lx", regs->ebx);
	kernel->debug.Error("ebx:    0x%08lx", regs->ebx);
	kernel->debug.Error("esp:    0x%08lx", regs->esp);
	kernel->debug.Error("ebp:    0x%08lx", regs->ebp);
	kernel->debug.Error("esi:    0x%08lx", regs->esi);
	kernel->debug.Error("edi:    0x%08lx", regs->edi);
	kernel->debug.Error("eip:    0x%08lx", regs->eip);
	kernel->debug.Error("eflags: 0x%08lx", regs->eflags);

	kernel->debug.Error("Segs:");
	kernel->debug.Error("cs:     0x%08lx", regs->cs);
	kernel->debug.Error("ss:     0x%08lx", regs->ss);
	kernel->debug.Error("ds:     0x%08lx", regs->ds);
	kernel->debug.Error("es:     0x%08lx", regs->es);
	kernel->debug.Error("fs:     0x%08lx", regs->fs);
	kernel->debug.Error("gs:     0x%08lx", regs->gs);
}


/// @brief IRQ handler
/// @param regs 
extern "C" void IRQ_Handler(Registers* regs)
{
	//Send an EOI to the PICs
	if (regs->irq >= 32 && regs->irq <= 47)
	{
		if (regs->irq >= 40) PortByteOut(PIC2_CMD, PIC_EOI); //slave
		if (regs->irq >= 32) PortByteOut(PIC1_CMD, PIC_EOI); //master
	}

	//Output stacked info
	if (regs->irq >= 0 && regs->irq <= 18)
	{
		StackedInfo(regs);
	}

	//Handle the interrupt in a more modular way
	kernel->interrupt.Handler(regs->irq);
}
