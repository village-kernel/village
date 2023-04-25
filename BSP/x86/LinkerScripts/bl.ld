ENTRY(_start)

_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Heap_Size  = 0x400;
_Min_Stack_Size = 0x800;

MEMORY
{
	RAM (xrw)    : ORIGIN = 0x1000, LENGTH = 1M
}

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)
		. = ALIGN(4);
	} > RAM

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > RAM

	.data :
	{
		. = ALIGN(4);
		_sdata = .;  
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .; 
	} > RAM

	.bss :
	{
		. = ALIGN(4);
		_sbss = .; 
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		_ebss = .; 
	} > RAM

	._user_heap_stack :
	{
		. = ALIGN(4);
		PROVIDE ( end = . );
		PROVIDE ( _end = . );
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(4);
	} > RAM
}
