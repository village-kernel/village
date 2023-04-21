############################################################################
# boot.s
# x86_64 boot file
#
# $Copyright: Copyright (C) village
############################################################################

BOOTSEG		= 0x07C0		/* original address of boot-sector */

	.code16
    .section ".text", "ax"
	.global  _start

_start:
	# Normalize the start address
	ljmp $BOOTSEG, $start2

start2:
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $0x8000, %bp
	movw %bp, %sp

	movw $bootMsg, %bx
	call PrintString

	movw $diskLoadMsg, %bx
	call PrintString

	movw $0x1234, %dx
	call PrintHex

loop:
	jmp loop

#include "BootPrint.s"
#include "BootGPT.s"

bootMsg:
	.asciz "Hello, OS world!"

diskLoadMsg:
	.asciz "Loading data from disk!"

diskErrorMsg:
	.asciz "Disk error!"

switchPmMsg:
	.asciz "Switch protected mode..."

BootSectionEnd:
	.org	510
	.word	0xaa55

