############################################################################
# boot.s
# x86_64 boot file
#
# $Copyright: Copyright (C) village
############################################################################
.org 0
.code16
.section ".text", "ax"

estack16 = 0x9000
estack32 = 0x90000
bootloader = 0x1000

.global _start
_start:
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $estack16, %bp
	movw %bp, %sp

	call LoadBootLoader
	call SwitchToPM
	jmp .


LoadBootLoader:
	movw $bootloader, %bx
	movb $2, %dh
	call ReadDisk
	ret

SwitchToPM:
	# disable interrupts
	cli

	# load the GDT descriptor
	lgdt gdtDescriptor

	# set 32-bit mode bit in cr0
	mov %cr0, %eax 
	or  $0x1, %eax
	mov %eax, %cr0

	# far jump by using a different segment
	ljmp $codeSeg, $InitPM  


#include "BootDisk.s"
#include "BootGPT.s"
#include "BootPrint.s"

.code32
	InitPM:
	# update segment
	movw $dataSeg, %ax 
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	# update stack
	movl $estack32, %ebp  
	movl %ebp, %esp 

	# call bootloader
	call bootloader
	jmp .

bootSectionEnd:
	.org	510
	.word	0xaa55
