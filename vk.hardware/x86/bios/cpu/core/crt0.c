//###########################################################################
// crt0.s
// Low level file that manages program entry
//
// $Copyright: Copyright (C) village
//###########################################################################

/// @brief program entry main
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[]);


/// @brief Initialize data and bss section
/// @param  
void __init_data_bss(void)
{
	extern void *_sidata, *_sdata, *_edata;
	extern void *_sbss,   *_ebss;

	void **pSource, **pDest;

	//Copy data segment initializers from disk to SRAM
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	//Zero fill the bss segment.
	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
}


/// @brief execute preinit_arrary
/// @param  
void __preinit_arrary(void)
{
	extern void (*__preinit_array_start []) (void);
	extern void (*__preinit_array_end   []) (void);

	int count = __preinit_array_end - __preinit_array_start;
	for (int i = 0; i < count; i++)
		__preinit_array_start[i]();
}


/// @brief execute init_arrary
/// @param  
void __init_array(void)
{
	extern void (*__init_array_start []) (void);
	extern void (*__init_array_end   []) (void);

	int count = __init_array_end - __init_array_start;
	for (int i = 0; i < count; i++)
		__init_array_start[i]();
}


/// @brief execute fini_arrary
/// @param  
void __fini_array(void)
{
	extern void (*__fini_array_start []) (void);
	extern void (*__fini_array_end   []) (void);

	int count = __fini_array_end - __fini_array_start;
	
	for (int i = 0; i < count; i++)
	{
		__fini_array_start[i]();
	}
}


/// @brief _start
/// @param  
void __attribute__((naked, noreturn))_start(int argc, char* argv[])
{
	__init_data_bss();

	__preinit_arrary();

	__init_array();
	
	main(argc, argv);
	
	__fini_array();
}
