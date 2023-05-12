//###########################################################################
// Thread.cpp
// Definitions of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Interrupt.h"
#include "Environment.h"
#include "Registers.h"
#include "HalHeaders.h"


/// @brief Constructor
Interrupt::Interrupt()
{
}


/// @brief Fini constructor
Interrupt::~Interrupt()
{
}


/// @brief Singleton Instance
/// @return Interrupt instance
Interrupt& Interrupt::Instance()
{
	static Interrupt instance;
	return instance;
}
EXPORT_SYMBOL(Interrupt::Instance, _ZN9Interrupt8InstanceEv);


/// @brief Definitions interrupt and export
Interrupt& interrupt = Interrupt::Instance();
Interrupt* pinterrupt = &interrupt;
EXPORT_SYMBOL(pinterrupt, interrupt);


/// @brief Interrupt initialize
void Interrupt::Initialize()
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
	PortByteOut(0x20, 0x11);  //restart PIC1
	PortByteOut(0xA0, 0x11);  //restart PIC2
	PortByteOut(0x21, 0x20);  //PIC1 now starts at 32
	PortByteOut(0xA1, 0x28);  //PIC2 now starts at 40
	PortByteOut(0x21, 0x04);  //setup cascading
	PortByteOut(0xA1, 0x02);
	PortByteOut(0x21, 0x01);  //done!
	PortByteOut(0xA1, 0x01);
	PortByteOut(0x21, 0x0);
	PortByteOut(0xA1, 0x0);

	//Load with ASM
	SetIdt();
}


/// @brief Set idt gate
/// @param irq 
/// @param handler 
void Interrupt::SetIdtGate(int irq, uint32_t handler)
{
    idt[irq].lowOffset = (uint16_t)((handler) & 0xFFFF);
    idt[irq].sel = kernel_code_segment;
    idt[irq].flags = 0x8E; 
    idt[irq].highOffset = (uint16_t)(((handler) >> 16) & 0xFFFF);
}


/// @brief Set idt
void Interrupt::SetIdt()
{
    idtReg.base = (uint32_t) &idt;
    idtReg.limit = idt_entires * sizeof(IdtGate) - 1;
    /* Don't make the mistake of loading &idt -- always load &idtReg */
    __asm volatile("lidtl (%0)" : : "r" (&idtReg));
}


/// @brief Interrupt Set ISR
/// @param irq irq number
/// @param func interupt function
/// @param argv interrupt argv
void Interrupt::SetISR(int irq, Function func, char* argv)
{
	isrTabs[irq].Add(new Isr(irq, func, argv));
}


/// @brief Interrupt clear isr
/// @param irq irq number
/// @param func interrupt function
/// @param argv interrupt argv
void Interrupt::ClearISR(int irq, Function func, char* argv)
{
	List<Isr> isrs = isrTabs[irq];

	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		if ((irq  == isr->irq ) &&
			(func == isr->func) &&
			(argv == isr->argv))
		{
			isrs.Remove(isr, isrs.GetNid()); break;
		}
	}
}


/// @brief Interrupt handler
/// @param irq irq number
void Interrupt::Handler(int irq)
{
	List<Isr> isrs = interrupt.isrTabs[irq];
	
	for (Isr* isr = isrs.Begin(); !isrs.IsEnd(); isr = isrs.Next())
	{
		(isr->func)(isr->argv);
	}
}


/// @brief IRQ handler
/// @param regs 
extern "C" void IRQ_Handler(Registers regs)
{
    //After every interrupt we need to send an EOI to the PICs
    //or they will not send another interrupt again
    if (regs.irq >= 32 && regs.irq < 40)
		PortByteOut(0x20, 0x20); //master
	else if (regs.irq >= 40)
		PortByteOut(0xA0, 0x20); //slave

    //Handle the interrupt in a more modular way
	Interrupt::Handler(regs.irq);
}
