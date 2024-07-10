//###########################################################################
// crt0_kernel.c
// Low level file that manages kernel entry
//
// $Copyright: Copyright (C) village
//###########################################################################

/// @brief program entry main
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[]);


/// @brief _start
/// @param argc 
/// @param argv 
void _start(int argc, char* argv[]);


/// @brief IRQ_Handler
void __attribute__ ((weak, naked)) IRQ_Handler()
{
	__asm("jmp .");
}


/// @brief Stub_Handler
void __attribute__ ((weak, naked)) Stub_Handler() 
{
	//Push data into esp
	__asm("pushl %ds");
	__asm("pushl %es");
	__asm("pushl %fs");
	__asm("pushl %gs");
	__asm("pushal");

	//Sets the segments
	__asm("movw $0x10, %ax");
	__asm("movw %ax, %ds");
	__asm("movw %ax, %es");
	__asm("movw %ax, %fs");
	__asm("movw %ax, %gs");
    
	//Call IRQ_Handler(%esp)
	__asm("pushl %esp");
	__asm("call IRQ_Handler");
	__asm("addl $4, %esp");

	//Pop all data back
	__asm("popal");
	__asm("popl %gs");
	__asm("popl %fs");
	__asm("popl %es");
	__asm("popl %ds");

	//Skip irq and errcode
	__asm("add  $8, %esp ");
	__asm("sti");
	__asm("iret");
}


/// @brief Division_By_Zero_Handler
void __attribute__ ((weak, naked)) Division_By_Zero_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $0");
	__asm("jmp Stub_Handler");
}


/// @brief Debug_Handler
void __attribute__ ((weak, naked)) Debug_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $1");
	__asm("jmp Stub_Handler");
}


/// @brief Non_Maskable_Interrupt_Handler
void __attribute__ ((weak, naked)) Non_Maskable_Interrupt_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $2");
	__asm("jmp Stub_Handler");
}


/// @brief Breakpoint_Handler
void __attribute__ ((weak, naked)) Breakpoint_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $3");
	__asm("jmp Stub_Handler");
}


/// @brief Into_Detected_Overflow_Handler
void __attribute__ ((weak, naked)) Into_Detected_Overflow_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $4");
	__asm("jmp Stub_Handler");
}


/// @brief Out_Of_Bounds_Handler
void __attribute__ ((weak, naked)) Out_Of_Bounds_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $5");
	__asm("jmp Stub_Handler");
}


/// @brief Invalid_Opcode_Handler
void __attribute__ ((weak, naked)) Invalid_Opcode_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $6");
	__asm("jmp Stub_Handler");
}


/// @brief No_Coprocessor_Handler
void __attribute__ ((weak, naked)) No_Coprocessor_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $7");
	__asm("jmp Stub_Handler");
}


/// @brief Doule_Fault_Handler
void __attribute__ ((weak, naked)) Doule_Fault_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $8");
	__asm("jmp Stub_Handler");
}


/// @brief Coprocessor_Segment_Overrun_Handler
void __attribute__ ((weak, naked)) Coprocessor_Segment_Overrun_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $9");
	__asm("jmp Stub_Handler");
}


/// @brief Bad_TSS_Handler
void __attribute__ ((weak, naked)) Bad_TSS_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $10");
	__asm("jmp Stub_Handler");
}


/// @brief Segment_Not_Present_Handler
void __attribute__ ((weak, naked)) Segment_Not_Present_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $11");
	__asm("jmp Stub_Handler");
}


/// @brief Stack_Fault_Handler
void __attribute__ ((weak, naked)) Stack_Fault_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $12");
	__asm("jmp Stub_Handler");
}


/// @brief General_Protection_Fault_Handler
void __attribute__ ((weak, naked)) General_Protection_Fault_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $13");
	__asm("jmp Stub_Handler");
}


/// @brief Page_Fault_Handler
void __attribute__ ((weak, naked)) Page_Fault_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $14");
	__asm("jmp Stub_Handler");
}


/// @brief Unknown_Interrupt_Handler
void __attribute__ ((weak, naked)) Unknown_Interrupt_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $15");
	__asm("jmp Stub_Handler");
}


/// @brief Coprocessor_Fault_Handler
void __attribute__ ((weak, naked)) Coprocessor_Fault_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $16");
	__asm("jmp Stub_Handler");
}


/// @brief Alignment_Check_Handler
void __attribute__ ((weak, naked)) Alignment_Check_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $17");
	__asm("jmp Stub_Handler");
}


/// @brief Machine_Check_Handler
void __attribute__ ((weak, naked)) Machine_Check_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $18");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_19_Handler
void __attribute__ ((weak, naked)) Reserved_IN_19_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $19");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_20_Handler
void __attribute__ ((weak, naked)) Reserved_IN_20_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $20");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_21_Handler
void __attribute__ ((weak, naked)) Reserved_IN_21_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $21");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_22_Handler
void __attribute__ ((weak, naked)) Reserved_IN_22_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $22");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_23_Handler
void __attribute__ ((weak, naked)) Reserved_IN_23_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $23");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_24_Handler
void __attribute__ ((weak, naked)) Reserved_IN_24_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $24");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_25_Handler
void __attribute__ ((weak, naked)) Reserved_IN_25_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $25");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_26_Handler
void __attribute__ ((weak, naked)) Reserved_IN_26_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $26");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_27_Handler
void __attribute__ ((weak, naked)) Reserved_IN_27_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $27");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_28_Handler
void __attribute__ ((weak, naked)) Reserved_IN_28_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $28");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_IN_29_Handler
void __attribute__ ((weak, naked)) Reserved_IN_29_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $29");
	__asm("jmp Stub_Handler");
}


/// @brief SVC_Handler
void __attribute__ ((weak, naked)) SVC_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $30");
	__asm("jmp Stub_Handler");
}


/// @brief PendSV_Handler
void __attribute__ ((weak, naked)) PendSV_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $31");
	__asm("jmp Stub_Handler");
}


/// @brief SysTick_Handler
void __attribute__ ((weak, naked)) SysTick_Handler()
{
	__asm("cli");
	__asm("push $0");
	__asm("push $32");
	__asm("jmp Stub_Handler");
}


/// @brief Keyboard_Controller_Handler
void __attribute__ ((weak, naked)) Keyboard_Controller_Handler()
{
	__asm("cli");
	__asm("push $1");
	__asm("push $33");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_EX_2_Handler
void __attribute__ ((weak, naked)) Reserved_EX_2_Handler()
{
	__asm("cli");
	__asm("push $2");
	__asm("push $34");
	__asm("jmp Stub_Handler");
}


/// @brief Serial_Port_COM2_Handler
void __attribute__ ((weak, naked)) Serial_Port_COM2_Handler()
{
	__asm("cli");
	__asm("push $3");
	__asm("push $35");
	__asm("jmp Stub_Handler");
}


/// @brief Serial_Port_COM1_Handler
void __attribute__ ((weak, naked)) Serial_Port_COM1_Handler()
{
	__asm("cli");
	__asm("push $4");
	__asm("push $36");
	__asm("jmp Stub_Handler");
}


/// @brief Line_Print_Terminal2_Handler
void __attribute__ ((weak, naked)) Line_Print_Terminal2_Handler()
{
	__asm("cli");
	__asm("push $5");
	__asm("push $37");
	__asm("jmp Stub_Handler");
}


/// @brief Floppy_Controller_Handler
void __attribute__ ((weak, naked)) Floppy_Controller_Handler()
{
	__asm("cli");
	__asm("push $6");
	__asm("push $38");
	__asm("jmp Stub_Handler");
	__asm("sti");
}


/// @brief Line_Print_Terminal1_Handler
void __attribute__ ((weak, naked)) Line_Print_Terminal1_Handler()
{
	__asm("cli");
	__asm("push $7");
	__asm("push $39");
	__asm("jmp Stub_Handler");
}


/// @brief RTC_Timer_Handler
void __attribute__ ((weak, naked)) RTC_Timer_Handler()
{
	__asm("cli");
	__asm("push $8");
	__asm("push $40");
	__asm("jmp Stub_Handler");
}


/// @brief X86_Assembly_ACPI_Handler
void __attribute__ ((weak, naked)) X86_Assembly_ACPI_Handler()
{
	__asm("cli");
	__asm("push $9");
	__asm("push $41");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_EX_11_Handler
void __attribute__ ((weak, naked)) Reserved_EX_11_Handler()
{
	__asm("cli");
	__asm("push $10");
	__asm("push $42");
	__asm("jmp Stub_Handler");
}


/// @brief Reserved_EX_12_Handler
void __attribute__ ((weak, naked)) Reserved_EX_12_Handler()
{
	__asm("cli");
	__asm("push $11");
	__asm("push $43");
	__asm("jmp Stub_Handler");
}


/// @brief Mouse_Controller_Handler
void __attribute__ ((weak, naked)) Mouse_Controller_Handler()
{
	__asm("cli");
	__asm("push $12");
	__asm("push $44");
	__asm("jmp Stub_Handler");
}


/// @brief Math_Coprocessor_Handler
void __attribute__ ((weak, naked)) Math_Coprocessor_Handler()
{
	__asm("cli");
	__asm("push $13");
	__asm("push $45");
	__asm("jmp Stub_Handler");
}


/// @brief ATA_Channel1_Handler
void __attribute__ ((weak, naked)) ATA_Channel1_Handler()
{
	__asm("cli");
	__asm("push $14");
	__asm("push $46");
	__asm("jmp Stub_Handler");
}


/// @brief ATA_Channel2_Handler
void __attribute__ ((weak, naked)) ATA_Channel2_Handler()
{
	__asm("cli");
	__asm("push $15");
	__asm("push $47");
	__asm("jmp Stub_Handler");
}


/// @brief isr_vector
void * g_pfnVectors[] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_start,
	&Division_By_Zero_Handler,
	&Debug_Handler,
	&Non_Maskable_Interrupt_Handler,
	&Breakpoint_Handler,
	&Into_Detected_Overflow_Handler,
	&Out_Of_Bounds_Handler,
	&Invalid_Opcode_Handler,
	&No_Coprocessor_Handler,
	&Doule_Fault_Handler,
	&Coprocessor_Segment_Overrun_Handler,
	&Bad_TSS_Handler,
	&Segment_Not_Present_Handler,
	&Stack_Fault_Handler,
	&General_Protection_Fault_Handler,
	&Page_Fault_Handler,
	&Unknown_Interrupt_Handler,
	&Coprocessor_Fault_Handler,
	&Alignment_Check_Handler,
	&Machine_Check_Handler,
	&Reserved_IN_19_Handler,
	&Reserved_IN_20_Handler,
	&Reserved_IN_21_Handler,
	&Reserved_IN_22_Handler,
	&Reserved_IN_23_Handler,
	&Reserved_IN_24_Handler,
	&Reserved_IN_25_Handler,
	&Reserved_IN_26_Handler,
	&Reserved_IN_27_Handler,
	&Reserved_IN_28_Handler,
	&Reserved_IN_29_Handler,
	&SVC_Handler,
	&PendSV_Handler,
	&SysTick_Handler,
	&Keyboard_Controller_Handler,
	&Reserved_EX_2_Handler,
	&Serial_Port_COM2_Handler,
	&Serial_Port_COM1_Handler,
	&Line_Print_Terminal2_Handler,
	&Floppy_Controller_Handler,
	&Line_Print_Terminal1_Handler,
	&RTC_Timer_Handler,
	&X86_Assembly_ACPI_Handler,
	&Reserved_EX_11_Handler,
	&Reserved_EX_12_Handler,
	&Mouse_Controller_Handler,
	&Math_Coprocessor_Handler,
	&ATA_Channel1_Handler,
	&ATA_Channel2_Handler,
};


/// @brief Initialize data and bss section
/// @param  
void __init_data_bss(void)
{
	extern void *_sidata, *_sdata, *_edata;
	extern void *_sbss,   *_ebss;

	void **pSource, **pDest;

	//Copy data segment initializers from disk to SRAM
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	//Zero fill the bss segment.
	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
}


/// @brief execute preinit_arrary
/// @param  
void __preinit_arrary(void)
{
	extern void (*__preinit_array_start []) (void);
	extern void (*__preinit_array_end   []) (void);

	int count = __preinit_array_end - __preinit_array_start;
	for (int i = 0; i < count; i++)
		__preinit_array_start[i]();
}


/// @brief execute init_arrary
/// @param  
void __init_array(void)
{
	extern void (*__init_array_start []) (void);
	extern void (*__init_array_end   []) (void);

	int count = __init_array_end - __init_array_start;
	for (int i = 0; i < count; i++)
		__init_array_start[i]();
}


/// @brief execute fini_arrary
/// @param  
void __fini_array(void)
{
	extern void (*__fini_array_start []) (void);
	extern void (*__fini_array_end   []) (void);

	int count = __fini_array_end - __fini_array_start;
	
	for (int i = 0; i < count; i++)
	{
		__fini_array_start[i]();
	}
}


/// @brief _start
/// @param  
void _start(int argc, char* argv[])
{
	__init_data_bss();

	__preinit_arrary();

	__init_array();
	
	main(argc, argv);
	
	__fini_array();

	for(;;) ;
}
