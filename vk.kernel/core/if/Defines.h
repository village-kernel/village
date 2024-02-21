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


/// @brief Execute result defines
enum Result
{
	_OK     = 0,
	_ERR    = 1,
};


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


/// @brief Module id defines
enum ModuleID
{
	_system = 0,
	_device,
	_modular,
	_debug,
	_memory,
	_archInterrupt,
	_interrupt,
	_exception,
	_environment,
	_thread,
	_scheduler,
	_fileSystem,
	_input,
	_workQueue,
	_loader,
	_application = 101,
};


/// @brief driver
class Driver;


/// @brief module
class Module;


/// @brief DriverInfo
struct DriverInfo
{
	uint32_t  id;
	char*     name;
	Driver*   driver;
};


/// @brief ModuleInfo
struct ModuleInfo
{
	uint32_t  id;
	char*     name;
	Module*   module;
};


/// @brief SymbolInfo
struct SymbolInfo
{
	char*    name;
	uint32_t addr;
};


///Driver register macro
#define REGISTER_DRIVER(drv, id, name)                                                     \
static struct _Drv_##name {                                                                \
	uint32_t drvId; char* drvName; Driver* driver;                                         \
	_Drv_##name() { drvId = id; drvName = (char*)#name; static drv name; driver = &name; } \
} const _drv_##name __attribute__((used,__section__(".drivers")))


///Module register macro
#define REGISTER_MODULE(mod, id, name)                                                     \
static struct _Mod_##name {                                                                \
	uint32_t modId; char* modName; Module* module;                                         \
	_Mod_##name() { modId = id; modName = (char*)#name; static mod name; module = &name; } \
} const _mod_##name __attribute__((used,__section__(".modules")))


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
	#define EXPORT_SYMBOL_ALIAS(symbol, name)                                  \
	static struct _Sym_##name {                                                \
		char* symName; uint32_t symAddr;                                       \
		_Sym_##name() { symName = (char*)#name; marco_cast(symbol, symAddr); } \
	} const _sym_##name __attribute__((used,__section__(".symbols")))

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)          EXPORT_SYMBOL_ALIAS(symbol, symbol) 
#endif


#endif //!__DEFINES_H__
