############################################################################
# BootSection.s
# x86_64 boot section, loading bootloader and switch to protected mode
#
# $Copyright: Copyright (C) village
############################################################################
.org 0
.code16
.section ".text", "ax"

.set estack16,   0x9000
.set estack32,   0x90000
.set bootloader, 0x1000
.set bootCount,  0x11

.global _start
_start:
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $estack16, %bp
	movw %bp, %sp

	call ReadBootLoader
	call SwitchToProtectedMode
	jmp  .

# Loading bootloader from disk 
ReadBootLoader:
	movw $bootloader, %bx   # Read into bootloader
	movb $bootCount,  %dh   # The counts of read sector 
	call ReadFromDisk
	ret

# Read data from disk
ReadFromDisk:
	pusha
	push %dx                # Store DX on stack so later we can recall
	                        # how many sectors were request to be read,
						    # even if it is altered in the meantime

	movb $0x02, %ah         # BIOS read sector function
	movb %dh,   %al         # Read DH sector
	movb $0x00, %ch         # Select cylinder 0
	movb $0x02, %cl         # Start reading from second sector
	movb $0x00, %dh         # Select head 0
	int  $0x13              # Disk interrupt

	jc   DiskError          # Jump if error (i.e. carry flag set)

	pop  %dx                # Restore DX from the stack
	cmp  %dh, %al           # If AL (sectors read) != DH (sector expected)
	jne  DiskError          # Display error message
	popa
	ret

# Display disk error message
DiskError:
	movw $diskErrMsg, %ax   # Set the display msg address
	movw %ax,     %bp
	movw $0x1301, %ax       # Display string
	movw $0x000c, %bx       # Page 0, Red on black
	movw $21,     %cx       # String length
	movw $0,      %dx       # Show in where, dh: row dl: col
	int  $0x10              # Display interrupt
	jmp  .

diskErrMsg: .asciz "Load from disk error!"

# GDT start label
gdtStart:
	# the GDT starts with a null 8-byte
	.long 0x0               # 4 byte
	.long 0x0               # 4 byte

# GDT for code segment. base = 0x00000000, length = 0xfffff for flags
gdtCode: 
	.word 0xffff            # segment length, bits 0-15
	.word 0x0               # segment base, bits 0-15
	.byte 0x0               # segment base, bits 16-23
	.byte 0x9a              # 10011010b # flags (8 bits)
	.byte 0xcf              # 11001111b # flags (4 bits) + segment length, bits 16-19
	.byte 0x0               # segment base, bits 24-31

# GDT for data segment. base and length identical to code segment some flags changed again
gdtData:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x92              # 10010010b
	.byte 0xcf              # 11001111b
	.byte 0x0

# GDT end label
gdtEnd:

# GDT descriptor
gdtDescriptor:
	.word gdtEnd - gdtStart - 1 # size (16 bit), always one less of its true size
	.long gdtStart              # address (32 bit)

# define some constants for later use
codeSeg = gdtCode - gdtStart
dataSeg = gdtData - gdtStart

# Switch to protected mode
SwitchToProtectedMode:
	cli                     # disable interrupts
	lgdt gdtDescriptor      # load the GDT descriptor
	mov  %cr0, %eax 
	or   $0x1, %eax         # set 32-bit mode bit in cr0
	mov  %eax, %cr0
	ljmp $codeSeg, $Setup   # far jump by using a different segment

# Setup segment, stack and goto bootloader
.code32
Setup:
	movw $dataSeg, %ax      # update segment
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	
	movl $estack32, %ebp    # update stack
	movl %ebp, %esp 

	call bootloader         # call bootloader
	jmp  .

# boot section end
bootSectionEnd:
	.org	510
	.word	0xaa55          # Magic word
