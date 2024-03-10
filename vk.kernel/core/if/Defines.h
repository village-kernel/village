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


/// @brief driver
class Driver;


/// @brief component
class Component;


/// @brief DriverInfo
struct DriverInfo
{
	uint32_t  id;
	char*     name;
	Driver*   body;
};


/// @brief ComponentInfo
struct ComponentInfo
{
	uint32_t   id;
	char*      name;
	Component* body;
};


/// @brief SymbolInfo
struct SymbolInfo
{
	char*    name;
	uint32_t addr;
};


#ifdef BUILD_IN_MODULE
	///Driver register macro
	#define REGISTER_DRIVER(drv, id, name)                                                     \
	static struct _Drv_##name {                                                                \
		_Drv_##name() { static drv name; name.SetID(id); name.SetName((char*)#name);           \
		kernel->device->RegisterDriver(&name); }                                               \
	} const _drv_##name __attribute__((used,__section__(".drivers")))


	///Component register macro
	#define REGISTER_COMPONENT(cmp, id, name)                                                  \
	static struct _Cmp_##name {                                                                \
		_Cmp_##name() { static cmp name; name.SetID(id); name.SetName((char*)#name);           \
		kernel->feature->RegisterComponent(&name); }                                           \
	} const _cmp_##name __attribute__((used,__section__(".components")))
#else
	///Driver register macro
	#define REGISTER_DRIVER(drv, id, name)                                                     \
	static struct _Drv_##name {                                                                \
		uint32_t drvId; char* drvName; Driver* body;                                           \
		_Drv_##name() { static drv name; drvId = id; drvName = (char*)#name; body = &name; }   \
	} const _drv_##name __attribute__((used,__section__(".drivers")))


	///Component register macro
	#define REGISTER_COMPONENT(cmp, id, name)                                                  \
	static struct _Cmp_##name {                                                                \
		uint32_t cmpId; char* cmpName; Component* body;                                        \
		_Cmp_##name() { static cmp name; cmpId = id; cmpName = (char*)#name; body = &name; }   \
	} const _cmp_##name __attribute__((used,__section__(".components")))
#endif

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

#ifdef BUILD_IN_MODULE
	///Export symbol marco
	#define EXPORT_SYMBOL_ALIAS(symbol, name)                                  \
	static struct _Sym_##name {                                                \
		_Sym_##name() { uint32_t symAddr; marco_cast(symbol, symAddr);         \
		kernel->symbol->Export(symAddr, (char*)#name); }                       \
	} const _sym_##name __attribute__((used,__section__(".symbols")))
#else
	///Export symbol marco
	#define EXPORT_SYMBOL_ALIAS(symbol, name)                                  \
	static struct _Sym_##name {                                                \
		char* symName; uint32_t symAddr;                                       \
		_Sym_##name() { symName = (char*)#name; marco_cast(symbol, symAddr); } \
	} const _sym_##name __attribute__((used,__section__(".symbols")))
#endif

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)          EXPORT_SYMBOL_ALIAS(symbol, symbol) 
#endif


#endif //!__DEFINES_H__
