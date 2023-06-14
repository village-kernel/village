//###########################################################################
// crt0.s
// Low level file that manages system boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################

.code32
.global  _start

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
