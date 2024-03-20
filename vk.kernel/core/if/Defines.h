//###########################################################################
// Defines.h
// Declarations of the interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"


/// @brief Driver id defines
enum DriverID
{
	_serial              = 1,
	_storage             = 21,
	_timer               = 41,
	_display             = 61,
	_network             = 81,
	_usbdev              = 101,
	_usbhost             = 151,
	_miscdev             = 201,
};


/// @brief Component id defines
enum ComponentID
{
	_system = 1,
	_device,
	_feature,
	_debug,
	_memory,
	_archInterrupt,
	_interrupt,
	_exception,
	_symbol,
	_thread,
	_scheduler,
	_fileSystem,
	_input,
	_workQueue,
	_loader,
};


///init exit macro
#define __init __attribute__((constructor(101)))
#define __exit __attribute__((destructor(101)))


///Driver register macro
#define REGISTER_DRIVER(drv, id, name)                     \
drv p##name;                                               \
static void __init _Drv_ctor_##name()                      \
{                                                          \
	p##name.SetID(id);                                     \
	p##name.SetName((char*)#name);                         \
	kernel->device->RegisterDriver(&p##name);              \
}                                                          \
static void __exit _Drv_dtor_##name()                      \
{                                                          \
	kernel->device->DeregisterDriver(&p##name);            \
}    


///Component register macro
#define REGISTER_COMPONENT(cmp, id, name)                  \
cmp p##name;                                               \
static void __init _Cmp_ctor_##name()                      \
{                                                          \
	p##name.SetID(id);                                     \
	p##name.SetName((char*)#name);                         \
	kernel->feature->RegisterComponent(&p##name);          \
}                                                          \
static void __exit _Cmp_dtor_##name()                      \
{                                                          \
	kernel->feature->RegisterComponent(&p##name);          \
}


///Environment marco
#ifdef KBUILD_NO_ENVIRONNEMNT
	///Export symbol marco
	#define EXPORT_SYMBOL_ALIAS(symbol, name)  /*export symbol alias*/

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)              /*export symbol*/
#else
	///Get method address
#if defined(ARCH_X86)
	#define marco_cast(src, addr)  __asm volatile("movl $"#src", %0" : "=r"(addr))
#elif defined(ARCH_ARM)
	#define marco_cast(src, addr)  __asm volatile("ldr %0, ="#src : "=r"(addr))
#endif
	///Export symbol marco
	#define EXPORT_SYMBOL_ALIAS(sym, name)                 \
	static void __init _Sym_ctor_##name()                  \
	{                                                      \
		uint32_t symAddr = 0;                              \
		marco_cast(sym, symAddr);                          \
		kernel->symbol->Export(symAddr, (char*)#name);     \
	}                                                      \
	static void __exit _Sym_dtor_##name()                  \
	{                                                      \
		kernel->symbol->Unexport((char*)#name);            \
	}

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)          EXPORT_SYMBOL_ALIAS(symbol, symbol) 
#endif


#endif //!__DEFINES_H__
