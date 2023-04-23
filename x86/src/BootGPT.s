gdtStart: # don't remove the labels, they're needed to compute sizes and jumps
	# the GDT starts with a null 8-byte
	.long 0x0 # 4 byte
	.long 0x0 # 4 byte

# GDT for code segment. base = 0x00000000, length = 0xfffff for flags
gdtCode: 
	.word 0xffff    # segment length, bits 0-15
	.word 0x0       # segment base, bits 0-15
	.byte 0x0       # segment base, bits 16-23
	.byte 0x9a      # 10011010b # flags (8 bits)
	.byte 0xcf      # 11001111b # flags (4 bits) + segment length, bits 16-19
	.byte 0x0       # segment base, bits 24-31

# GDT for data segment. base and length identical to code segment some flags changed again
gdtData:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0x92      # 10010010b
	.byte 0xcf      # 11001111b
	.byte 0x0

gdtEnd:

# GDT descriptor
gdtDescriptor:
	.word gdtEnd - gdtStart - 1 # size (16 bit), always one less of its true size
	.long gdtStart # address (32 bit)

# define some constants for later use
codeSeg = gdtCode - gdtStart
dataSeg = gdtData - gdtStart
