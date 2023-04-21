PrintString:
	pusha                 # push all registers
PrintLoop:
	movb (%bx),  %al      # al = *bx
	call PrintChar        
	inc  %bx              # bx++
	cmpb $0x00, (%bx)     # if (0x00 != bx) PrintLoop
	jne  PrintLoop
	call PrintNewLine     # print new line
	popa                  # pop all registers
	ret

PrintHex:
	pusha
	
	movb $0x30, %al       # 0 ascii code is 0x30
	call PrintChar
	movb $0x78, %al       # x ascii code is 0x78
	call PrintChar

	movb %dh,   %al
	shr  $0x04, %al
	and  $0x0f, %al
	addb $0x30, %al
	call PrintChar

	movb %dh,   %al
	shr  $0x00, %al
	and  $0x0f, %al
	addb $0x30, %al
	call PrintChar

	movb %dl,   %al
	shr  $0x04, %al
	and  $0x0f, %al
	addb $0x30, %al
	call PrintChar

	movb %dl,   %al
	shr  $0x00, %al
	and  $0x0f, %al
	addb $0x30, %al
	call PrintChar

	call PrintNewLine
	popa
	ret

PrintChar:
	movb $0x0e, %ah       # Display in TTY mode
	int  $0x10
	ret

PrintNewLine:
	movb $0x0d, %al       # \r ascii code is 0x0d
	call PrintChar
	movb $0x0a, %al       # \n ascii code is 0x0a
	call PrintChar
	ret
