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
		void*       user;
		void*       args;

		Isr(int32_t irq = 0, Function func = NULL, void* user = NULL, void* args = NULL)
			:irq(irq),
			func(func),
			user(user),
			args(args)
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
	void RemapPIC();
public:
	//Methods
	void Initialize();
	int SetISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int SetISR(int irq, Method method, Class* user, void* args = NULL);
	int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int AppendISR(int irq, Method method, Class* user, void* args = NULL);
	int RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int RemoveISR(int irq, Method method, Class* user, void* args = NULL);
	void ClearISR(int irq);

	//Interrupt handler
	void Handler(int irq);
	uint16_t GetPicIrqReg(int ocw3);
	uint16_t GetPicIrr();
	uint16_t GetPicIsr();

	//Singleton Instance
	static Interrupt& Instance();
};

///Declarations interrupt reference
extern Interrupt& interrupt;

#endif //!__INTERRUPT_H__
