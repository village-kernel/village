//###########################################################################
// Interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "Templates.h"


//Interrupt
class Interrupt
{
private:
	//Structures
	struct Isr
	{
		int32_t     irq;
		Function    func;
		char*       argv;

		Isr(int32_t irq = 0, Function func = NULL, char* argv = NULL)
			:irq(irq),
			func(func),
			argv(argv)
		{}
	};

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
	static const uint32_t idt_entires = 256;

	//Members
	List<Isr> isrTabs[idt_entires];
	IdtGate idt[idt_entires];
	IdtRegister idtReg;

	//Methods
	Interrupt();
	~Interrupt();
	void SetIdtGate(int irq, uint32_t handler);
	void SetIdt();
public:
	//Methods
	void Initialize();
	void SetISR(int irq, Function isr, char* argv = NULL);
	void ClearISR(int irq, Function isr, char* argv = NULL);

	//Singleton Instance
	static Interrupt& Instance();
	
	//Interrupt handler
	static void Handler(int irq);
};

///Declarations interrupt reference
extern Interrupt& interrupt;

#endif //!__INTERRUPT_H__
