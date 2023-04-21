ENTRY(_start)

MEMORY
{
	RAM (xrw)    : ORIGIN = 0x0000, LENGTH = 512
}

SECTIONS
{
    .text :
	{
		. = ALIGN(8);
		*(.text)
		*(.text*)
		. = ALIGN(8);
	} > RAM

	.rodata :
	{
		. = ALIGN(8);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(8);
	} > RAM

	.data :
	{
		. = ALIGN(8);
		*(.data)
		*(.data*)
		. = ALIGN(8);
	} > RAM

	.bss :
	{
		. = ALIGN(8);
		*(.bss)
		*(.bss*)
		. = ALIGN(8);
	} > RAM
}
