
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
