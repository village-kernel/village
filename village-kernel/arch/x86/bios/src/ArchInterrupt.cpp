//###########################################################################
// ArchInterrupt.cpp
// Definitions of the functions that manage arch interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "ArchInterrupt.h"
#include "Interrupt.h"
#include "Hardware.h"
#include "Kernel.h"


/// @brief ArchInterrupt Setup
void ArchInterrupt::Setup()
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
		SetIdtGate(i - 1, (uint32_t)_svector[i]);
	}

	//Remap the PIC
	RemapPIC();

	//Set IDT
	SetIdt();
}


/// @brief ArchInterrupt Exit
void ArchInterrupt::Exit()
{

}


/// @brief Set idt gate
/// @param irq 
/// @param handler 
void ArchInterrupt::SetIdtGate(int irq, uint32_t handler)
{
	idt[irq].lowOffset = low_16(handler);
	idt[irq].highOffset = high_16(handler);
	idt[irq].sel = kernel_code_segment;
	idt[irq].flags = 0x8E; 
}


/// @brief Set idt
void ArchInterrupt::SetIdt()
{
	idtReg.base = (uint32_t)&idt;
	idtReg.limit = idt_entires * sizeof(IdtGate) - 1;
	__asm volatile("lidtl (%0)" : : "r" (&idtReg));
}


/// @brief Remap the PIC
void ArchInterrupt::RemapPIC()
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


/// @brief Get pic irq reg
/// @param ocw3 OCW3 to PIC CMD to get the register values PIC2 is chained, 
///             and represents IRQs 8-15. PIC1 is IRQs 0-7, with 2 being the chain
/// @return irq reg value
uint16_t ArchInterrupt::GetPicIrqReg(int ocw3)
{
	PortByteOut(PIC1_CMD, ocw3);
	PortByteOut(PIC2_CMD, ocw3);
	return (PortByteIn(PIC2_CMD) << 8) | PortByteIn(PIC1_CMD);
}


/// @brief Get PIC irr value
/// @return Returns the combined value of the cascaded PICs irq request register 
uint16_t ArchInterrupt::GetPicIrr()
{
	return GetPicIrqReg(PIC_READ_IRR);
}


/// @brief Get PIC isr value
/// @return Returns the combined value of the cascaded PICs in-service register
uint16_t ArchInterrupt::GetPicIsr()
{
	return GetPicIrqReg(PIC_READ_ISR);
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
