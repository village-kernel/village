ENTRY(Entry)

FORCE_GROUP_ALLOCATION

SECTIONS
{
	.text 0x00000000 :
	{
		*(.text)
		*(.text.*)
	}

	.rodata :
	{
		*(.rodata)
		*(.rodata1)
		*(.rodata.*)
	}

	.data :
	{
		*(.data)
		*(.data1)
		*(.data.*)
	}

	.bss :
	{
		*(.bss)
		*(.bss.*)
		*(.sbss)
		*(.sbss.*)
		*(COMMON)
	}

	.init_array :
	{
		*(SORT(.init_array.*))
		*(.init_array*)
		*(.ctors*)
	}

	.fini_array :
	{
		*(SORT(.fini_array.*))
		*(.fini_array*)
		*(.dtors*)
	}
}
