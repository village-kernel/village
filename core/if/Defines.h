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


///Execute result defines
enum Result
{
	_OK     = 0,
	_ERR    = 1,
};


///Driver id defines
enum DriverID
{
	_serial              = 1,
	_storage             = 21,
	_drvLoader           = 41,
	_display             = 61,
	_network             = 81,
	_usbdev              = 101,
	_usbhost             = 151,
	_miscdev             = 201,
};


///Module id defines
enum ModuleID
{
	_console             = 1,
	_libLoader           = 2,
	_modLoader           = 3,
	_workQueue           = 4,
	_executor            = 21,
	_application         = 101,
};


///Driver register macro
#define REGISTER_DRIVER(drv, id, name)                            \
static struct _Drv_##name {                                       \
	Driver* driver = drv;                                         \
	_Drv_##name() {                                               \
		Device::Instance().RegisterDriver(driver, id);            \
	}                                                             \
	~_Drv_##name() {                                              \
		Device::Instance().DeregisterDriver(driver, id);          \
	}                                                             \
} const _drv_##name __attribute__((used,__section__(".drivers")))


///Module register macro
#define REGISTER_MODULE(mod, id, name)                            \
static struct _Mod_##name {                                       \
	Module* module = mod;                                         \
	_Mod_##name() {                                               \
		Modular::Instance().RegisterModule(module, id);           \
	}                                                             \
	~_Mod_##name() {                                              \
		Modular::Instance().DeregisterModule(module, id);         \
	}                                                             \
} const _mod_##name __attribute__((used,__section__(".modules")))


///Environment marco
#ifdef KBUILD_NO_ENVIRONNEMNT
	///Export symbol marco
	#define EXPORT_SYMBOL(symbol, name)    /*export symbol*/

	///Search symbol marco
	#define SEARCH_SYMBOL(name)            (0)
#else
	///Get method address
#if defined(ARCH_X86)
	#define marco_cast(src, addr)  __asm volatile("movl $"#src", %0" : "=r"(addr))
#elif defined(ARCH_ARM)
	#define marco_cast(src, addr)  __asm volatile("mov %0, $"#src : "=r"(addr))
#endif

	///Export symbol marco
	#define EXPORT_SYMBOL_ALIAS(symbol, name)                                         \
	static struct _Sym_##name {                                                       \
		_Sym_##name() {                                                               \
			uint32_t symAddr = 0; marco_cast(symbol, symAddr);                        \
			Environment::Instance().ExportSymbol(symAddr, #name);                     \
		}                                                                             \
		~_Sym_##name() {                                                              \
			Environment::Instance().UnexportSymbol(#name);                            \
		}                                                                             \
	} const _sym_##name __attribute__((used,__section__(".symbols")))


	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)          EXPORT_SYMBOL_ALIAS(symbol, symbol) 


	///Search symbol marco
	#define SEARCH_SYMBOL(symbol)          Environment::Instance().SearchSymbol(symbol)
#endif


#endif //!__DEFINES_H__
