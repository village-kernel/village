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
	movw $0x100, %sp
	jmp  DispStr

DispStr:
	movw $BootMessage, %ax
	movw %ax, %bp
	movw $50, %cx
	movw $0x1301, %ax
	movw $0x000c, %bx
	movb $0, %dh
	movb $3, %dl
	int  $0x10

Loop:
	jmp Loop

BootMessage:
	.ascii	"Hello, OS world!"
	.org	510
	.word	0xaa55
