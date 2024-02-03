//###########################################################################
// ArchInterrupt.cpp
// Definitions of the functions that manage arch interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "ArchInterrupt.h"
#include "Interrupt.h"
#include "Registers.h"
#include "Hardware.h"
#include "Kernel.h"


/// @brief ConcreteArchInterrupt
class ConcreteArchInterrupt : public ArchInterrupt
{
private:
	//Structures
	struct IdtGate
	{
		uint16_t lowOffset;  /* Lower 16 bits of handler function address */
		uint16_t sel;        /* Kernel segment selector */
		uint8_t  rsvd;
		/* First byte
		* Bit 7: "Interrupt is present"
		* Bits 6-5: Privilege level of caller (0=kernel..3=user)
		* Bit 4: Set to 0 for interrupt gates
		* Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
		uint8_t  flags; 
		uint16_t highOffset; /* Higher 16 bits of handler function address */

		IdtGate() :
			lowOffset(0),
			sel(0),
			rsvd(0),
			flags(0),
			highOffset(0)
		{}
	} __attribute__((packed));

	struct IdtRegister
	{
		uint16_t limit;
		uint32_t base;
		
		IdtRegister() :
			limit(0),
			base(0)
		{}
	} __attribute__((packed));

	//Static constants
	static const uint32_t kernel_code_segment = 8;
	static const uint32_t idt_entires = isr_num;

	//Members
	IdtGate idt[idt_entires];
	IdtRegister idtReg;
private:
	/// @brief Set idt gate
	/// @param irq 
	/// @param handler 
	void SetIdtGate(int irq, uint32_t handler)
	{
		idt[irq].lowOffset = low_16(handler);
		idt[irq].highOffset = high_16(handler);
		idt[irq].sel = kernel_code_segment;
		idt[irq].flags = 0x8E; 
	}


	/// @brief Set idt
	void SetIdt()
	{
		idtReg.base = (uint32_t)&idt;
		idtReg.limit = idt_entires * sizeof(IdtGate) - 1;
		__asm volatile("lidtl (%0)" : : "r" (&idtReg));
	}


	/// @brief Remap the PIC
	void RemapPIC()
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
public:
	/// @brief ArchInterrupt initialize
	void Initialize()
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


	/// @brief Get pic irq reg
	/// @param ocw3 OCW3 to PIC CMD to get the register values PIC2 is chained, 
	///             and represents IRQs 8-15. PIC1 is IRQs 0-7, with 2 being the chain
	/// @return irq reg value
	uint16_t GetPicIrqReg(int ocw3)
	{
		PortByteOut(PIC1_CMD, ocw3);
		PortByteOut(PIC2_CMD, ocw3);
		return (PortByteIn(PIC2_CMD) << 8) | PortByteIn(PIC1_CMD);
	}


	/// @brief Get PIC irr value
	/// @return Returns the combined value of the cascaded PICs irq request register 
	uint16_t GetPicIrr()
	{
		return GetPicIrqReg(PIC_READ_IRR);
	}


	/// @brief Get PIC isr value
	/// @return Returns the combined value of the cascaded PICs in-service register
	uint16_t GetPicIsr()
	{
		return GetPicIrqReg(PIC_READ_ISR);
	}
};


/// @brief IRQ handler
/// @param regs 
extern "C" void IRQ_Handler(Registers regs)
{
	//Send an EOI to the PICs
	if (regs.irq >= 32 && regs.irq <= 47)
	{
		if (regs.irq >= 40) PortByteOut(PIC2_CMD, PIC_EOI); //slave
		if (regs.irq >= 32) PortByteOut(PIC1_CMD, PIC_EOI); //master
	}

	//Handle the interrupt in a more modular way
	kernel->interrupt->Handler(regs.irq);
}


///Register module
REGISTER_MODULE(ConcreteArchInterrupt, ModuleID::_archInterrupt, archInterrupt);
