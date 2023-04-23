
ReadDisk:
	pusha
	push %dx                # Store DX on stack so later we can recall
	                        # how many sectors were request to be read,
						    # even if it is altered in the meantime

	movb $0x02, %ah         # BIOS read sector function
	movb %dh,   %al         # Read DH sector
	movb $0x00, %ch         # Select cylinder 0
	movb $0x02, %cl         # Start reading from second sector
	movb $0x00, %dh         # Select head 0
	int $0x13

	jc DiskError            # Jump if error (i.e. carry flag set)

	pop %dx                 # Restore DX from the stack
	cmp %dh, %al            # If AL (sectors read) != DH (sector expected)
	jne DiskError           # Display error message
	popa
	ret

DiskError:
	movw $diskErrorMsg, %bx
	call PrintString
	jmp .

diskErrorMsg: .asciz "Disk error!"
