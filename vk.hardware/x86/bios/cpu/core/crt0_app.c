//###########################################################################
// crt0_app.s
// Low level file that manages application entry
//
// $Copyright: Copyright (C) village
//###########################################################################

/// @brief program entry main
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char* argv[]);


/// @brief fill bss zero
/// @param  
void __fill_bss_zero(void)
{
	extern void *_sbss, *_ebss;

	//Zero fill the bss segment.
	for (void **pDest = &_sbss; pDest != &_ebss; pDest++)
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
/// @param argc 
/// @param argv 
void _start(int argc, char* argv[])
{
	__fill_bss_zero();

	__preinit_arrary();

	__init_array();

	main(argc, argv);

	__fini_array();
}


/// @brief entry_vector
void * g_pfnVectors[] __attribute__ ((section (".entry_vector"), used)) = 
{
	&_start,
};
