//###########################################################################
// startup.s
// Low level file that manages system boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################

.code32
.global  g_pfnVectors
.global  _start
.extern  IRQ_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.long  _sidata
/* start address for the .data section. defined in linker script */  
.long  _sdata
/* end address for the .data section. defined in linker script */
.long  _edata
/* start address for the .bss section. defined in linker script */
.long  _sbss
/* end address for the .bss section. defined in linker script */
.long  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

	.section  .text._start
	.weak  _start
	.type  _start, %function
_start:
/* Copy the data segment initializers from flash to RAM */  
	movl $_sidata, %esi
	movl $_sdata,  %ebx
	jmp LoopCopyDataInit

CopyDataInit:
	movl (%esi), %eax
	movl  %eax, (%ebx)
	addl $4, %esi
	addl $4, %ebx

LoopCopyDataInit:
	cmpl $_edata, %ebx
	jne CopyDataInit

/* Zero fill the bss segment. */
	movl $_sbss, %ebx
	jmp LoopFillZeroboss

FillZerobss:
	movl $0, (%ebx)
	addl $4,  %ebx

LoopFillZeroboss:
	cmpl $_ebss, %ebx
	jne FillZerobss

	/* Call static constructors */
	call  __libc_init_array
	/* Call the application's entry point.*/
	call  main
	jmp  .
.size  _start, .-_start


/**
 * @brief  Common IRQ code. Identical to ISR code except for the 'call' and the 'pop ebx'
 * @param  None     
 * @retval None       
*/
	.section  .text.Stub_Handler,"ax",%progbits
Stub_Handler:
    pusha 
    movw %ds, %ax 
    push %eax
    movw $0x10, %ax 
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
    
	call IRQ_Handler
    
	pop  %eax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
    popa
    add  $8, %esp 
    sti
    iret
	.size  Stub_Handler, .-Stub_Handler


/******************************************************************************
*
* The minimal vector table for a x86. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
	.section  .isr_vector,"a",%progbits
	.type  g_pfnVectors, %object
	.size  g_pfnVectors, .-g_pfnVectors
	.align 32
	
g_pfnVectors:
	.long	_start
	.long	Division_By_Zero_Handler
	.long	Debug_Handler
	.long	Non_Maskable_Interrupt_Handler
	.long	Breakpoint_Handler
	.long	Into_Detected_Overflow_Handler
	.long	Out_Of_Bounds_Handler
	.long	Invalid_Opcode_Handler
	.long	No_Coprocessor_Handler
	.long	Doule_Fault_Handler
	.long	Coprocessor_Segment_Overrun_Handler
	.long	Bad_TSS_Handler
	.long	Segment_Not_Present_Handler
	.long	Stack_Fault_Handler
	.long	General_Protection_Fault_Handler
	.long	Page_Fault_Handler
	.long	Unknown_Interrupt_Handler
	.long	Coprocessor_Fault_Handler
	.long	Alignment_Check_Handler
	.long	Machine_Check_Handler
	.long	Reserved_IN_19_Handler
	.long	Reserved_IN_20_Handler
	.long	Reserved_IN_21_Handler
	.long	Reserved_IN_22_Handler
	.long	Reserved_IN_23_Handler
	.long	Reserved_IN_24_Handler
	.long	Reserved_IN_25_Handler
	.long	Reserved_IN_26_Handler
	.long	Reserved_IN_27_Handler
	.long	Reserved_IN_28_Handler
	.long	Reserved_IN_29_Handler
	.long	SVC_Handler
	.long	PendSV_Handler
	.long	SysTick_Handler
	.long	Keyboard_Controller_Handler
	.long	Reserved_EX_2_Handler
	.long	Serial_Port_COM2_Handler
	.long	Serial_Port_COM1_Handler
	.long	Line_Print_Terminal2_Handler
	.long	Floppy_Controller_Handler
	.long	Line_Print_Terminal1_Handler
	.long	RTC_Timer_Handler
	.long	X86_Assembly_ACPI_Handler
	.long	Reserved_EX_11_Handler
	.long	Reserved_EX_12_Handler
	.long	Mouse_Controller_Handler
	.long	Math_Coprocessor_Handler
	.long	ATA_Channel1_Handler

    
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* 
*******************************************************************************/
Division_By_Zero_Handler:
	cli
	push $0
	push $0
	jmp Stub_Handler

Debug_Handler:
	push $0
    push $1
	jmp Stub_Handler

Non_Maskable_Interrupt_Handler:
	push $0
    push $2
	jmp Stub_Handler

Breakpoint_Handler:
	push $0
    push $3
	jmp Stub_Handler

Into_Detected_Overflow_Handler:
	push $0
    push $4
	jmp Stub_Handler

Out_Of_Bounds_Handler:
	push $0
    push $5
	jmp Stub_Handler

Invalid_Opcode_Handler:
	push $0
    push $6
	jmp Stub_Handler

No_Coprocessor_Handler:
	push $0
    push $7
	jmp Stub_Handler

Doule_Fault_Handler:
	push $0
    push $8
	jmp Stub_Handler

Coprocessor_Segment_Overrun_Handler:
	push $0
    push $9
	jmp Stub_Handler

Bad_TSS_Handler:
	push $0
    push $10
	jmp Stub_Handler

Segment_Not_Present_Handler:
	push $0
    push $11
	jmp Stub_Handler

Stack_Fault_Handler:
	push $0
    push $12
	jmp Stub_Handler

General_Protection_Fault_Handler:
	push $0
    push $13
	jmp Stub_Handler

Page_Fault_Handler:
	push $0
    push $14
	jmp Stub_Handler

Unknown_Interrupt_Handler:
	push $0
    push $15
	jmp Stub_Handler

Coprocessor_Fault_Handler:
	push $0
    push $16
	jmp Stub_Handler

Alignment_Check_Handler:
	push $0
    push $17
	jmp Stub_Handler

Machine_Check_Handler:
	push $0
    push $18
	jmp Stub_Handler

Reserved_IN_19_Handler:
	push $0
    push $19
	jmp Stub_Handler

Reserved_IN_20_Handler:
	push $0
    push $20
	jmp Stub_Handler

Reserved_IN_21_Handler:
	push $0
    push $21
	jmp Stub_Handler

Reserved_IN_22_Handler:
	push $0
    push $22
	jmp Stub_Handler

Reserved_IN_23_Handler:
	push $0
    push $23
	jmp Stub_Handler

Reserved_IN_24_Handler:
	push $0
    push $24
	jmp Stub_Handler

Reserved_IN_25_Handler:
	push $0
    push $25
	jmp Stub_Handler

Reserved_IN_26_Handler:
	push $0
    push $26
	jmp Stub_Handler

Reserved_IN_27_Handler:
	push $0
    push $27
	jmp Stub_Handler

Reserved_IN_28_Handler:
	push $0
    push $28
	jmp Stub_Handler

Reserved_IN_29_Handler:
	push $0
    push $29
	jmp Stub_Handler

SVC_Handler:
	push $0
    push $30
	jmp Stub_Handler

PendSV_Handler:
	push $0
    push $31
	jmp Stub_Handler

SysTick_Handler:
	push $0
    push $32
	jmp Stub_Handler

Keyboard_Controller_Handler:
	push $1
    push $33
	jmp Stub_Handler

Reserved_EX_2_Handler:
	push $2
    push $34
	jmp Stub_Handler

Serial_Port_COM2_Handler:
	push $3
    push $35
	jmp Stub_Handler

Serial_Port_COM1_Handler:
	push $4
    push $36
	jmp Stub_Handler

Line_Print_Terminal2_Handler:
	push $5
    push $37
	jmp Stub_Handler

Floppy_Controller_Handler:
	push $6
    push $38
	jmp Stub_Handler

Line_Print_Terminal1_Handler:
	push $7
    push $39
	jmp Stub_Handler

RTC_Timer_Handler:
	push $8
    push $40
	jmp Stub_Handler

X86_Assembly_ACPI_Handler:
	push $9
    push $41
	jmp Stub_Handler

Mouse_Controller_Handler:
	push $10
    push $42
	jmp Stub_Handler

Reserved_EX_11_Handler:
	push $11
    push $43
	jmp Stub_Handler

Reserved_EX_12_Handler:
	push $12
    push $44
	jmp Stub_Handler

Math_Coprocessor_Handler:
	push $13
    push $45
	jmp Stub_Handler

ATA_Channel1_Handler:
	push $14
    push $46
	jmp Stub_Handler

ATA_Channel2_Handler:
	push $15
    push $47
	jmp Stub_Handler
