//###########################################################################
// crt0_app.cpp
// Low level file that manages application entry
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"

/// @brief Kernel
Kernel* kernel;

/// @brief image offset
extern uint32_t _IMGOFFS;

/// @brief dynamic header
extern uint32_t _DYNAMIC;


/// @brief setup kernel
/// @param kernel 
/// @return 
extern "C" void setup(void* knl)
{
	kernel = (Kernel*)knl;
}


/// @brief program entry main
/// @param argc 
/// @param argv 
/// @return 
extern "C" int main(int argc, char* argv[]);


/// @brief fill bss zero
/// @param  
extern "C" void __fill_bss_zero(void)
{
	extern void *_sbss, *_ebss;

	//Zero fill the bss segment.
	for (void **pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
}


/// @brief execute preinit_arrary
/// @param  
extern "C" void __preinit_arrary(void)
{
	extern void (*__preinit_array_start []) (void);
	extern void (*__preinit_array_end   []) (void);

	int count = __preinit_array_end - __preinit_array_start;
	for (int i = 0; i < count; i++)
		__preinit_array_start[i]();
}


/// @brief execute init_arrary
/// @param  
extern "C" void __init_array(void)
{
	extern void (*__init_array_start []) (void);
	extern void (*__init_array_end   []) (void);

	int count = __init_array_end - __init_array_start;
	for (int i = 0; i < count; i++)
		__init_array_start[i]();
}


/// @brief execute fini_arrary
/// @param  
extern "C" void __fini_array(void)
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
extern "C" void _start(void* kernel, int argc, char* argv[])
{
	__fill_bss_zero();

	setup(kernel);

	__preinit_arrary();

	__init_array();

	main(argc, argv);

	__fini_array();
}


/// @brief entry
void* g_pfnVectors[] __attribute__ ((section (".entry"), used)) = 
{	
	(void*)&_IMGOFFS,
	(void*)&_DYNAMIC,
	(void*)&_start,
};
