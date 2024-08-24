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
	_block,
	_character,
	_framebuffer,
	_network,
	_miscellaneous,
	_platformDevice,
	_platformDriver,
	_dirverIdSize,
};


/// @brief Module id defines
enum ModuleID
{
	_feature,
	_serivce,
	_program,
	_moduleIdSize,
};


///Block device register macro
#define REGISTER_BLOCK_DEVICE(dev, name)                          \
static struct _Block_Dev_##name {                                 \
	BlockDevice* device = dev;                                    \
	_Block_Dev_##name() {                                         \
		device->SetID(DriverID::_block);                          \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterBlockDevice(device);               \
	}                                                             \
	~_Block_Dev_##name() {                                        \
		kernel->device.UnregisterBlockDevice(device);             \
	}                                                             \
} const _block_dev_##name __attribute__((used,__section__(".devices")))


///Char device register macro
#define REGISTER_CHAR_DEVICE(dev, name)                           \
static struct _Char_Dev_##name {                                  \
	CharDevice* device = dev;                                     \
	_Char_Dev_##name() {                                          \
		device->SetID(DriverID::_character);                      \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterCharDevice(device);                \
	}                                                             \
	~_Char_Dev_##name() {                                         \
		kernel->device.UnregisterCharDevice(device);              \
	}                                                             \
} const _char_dev_##name __attribute__((used,__section__(".devices")))


///Framebuffer device register macro
#define REGISTER_FB_DEVICE(dev, name)                             \
static struct _FB_Dev_##name {                                    \
	FBDevice* device = dev;                                       \
	_FB_Dev_##name() {                                            \
		device->SetID(DriverID::_framebuffer);                    \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterFBDevice(device);                  \
	}                                                             \
	~_FB_Dev_##name() {                                           \
		kernel->device.UnregisterFBDevice(device);                \
	}                                                             \
} const _fb_dev_##name __attribute__((used,__section__(".devices")))


///Network device register macro
#define REGISTER_NETWORK_DEVICE(dev, name)                        \
static struct _Network_Dev_##name {                               \
	NetworkDevice* device = dev;                                  \
	_Network_Dev_##name() {                                       \
		device->SetID(DriverID::_network);                        \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterNetworkDevice(device);             \
	}                                                             \
	~_Network_Dev_##name() {                                      \
		kernel->device.UnregisterNetworkDevice(device);           \
	}                                                             \
} const _network_dev_##name __attribute__((used,__section__(".devices")))


///Misc device register macro
#define REGISTER_MISC_DEVICE(dev, name)                           \
static struct _Misc_Dev_##name {                                  \
	MiscDevice* device = dev;                                     \
	_Misc_Dev_##name() {                                          \
		device->SetID(DriverID::_miscellaneous);                  \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterMiscDevice(device);                \
	}                                                             \
	~_Misc_Dev_##name() {                                         \
		kernel->device.UnregisterMiscDevice(device);              \
	}                                                             \
} const _misc_dev_##name __attribute__((used,__section__(".devices")))


///Plat driver register macro
#define REGISTER_PLAT_DRIVER(drv, name)                           \
static struct _Plat_Drv_##name {                                  \
	PlatDriver* driver = drv;                                     \
	_Plat_Drv_##name() {                                          \
		driver->SetID(DriverID::_platformDriver);                 \
		driver->SetName((char*)#name);                            \
		kernel->device.RegisterPlatDriver(driver);                \
	}                                                             \
	~_Plat_Drv_##name() {                                         \
		kernel->device.UnregisterPlatDriver(driver);              \
	}                                                             \
} const _plat_drv_##name __attribute__((used,__section__(".devices")))


///Plat device register macro
#define REGISTER_PLAT_DEVICE(dev, name)                           \
static struct _Plat_Dev_##name {                                  \
	PlatDevice* device = dev;                                     \
	_Plat_Dev_##name() {                                          \
		device->SetID(DriverID::_platformDevice);                 \
		device->SetName((char*)#name);                            \
		kernel->device.RegisterPlatDevice(device);                \
	}                                                             \
	~_Plat_Dev_##name() {                                         \
		kernel->device.UnregisterPlatDevice(device);              \
	}                                                             \
} const _plat_dev_##name __attribute__((used,__section__(".devices")))


///Module register macro
#define REGISTER_MODULE(mod, id, name)                            \
static struct _Mod_##name {                                       \
	Module* module = mod;                                         \
	_Mod_##name() {                                               \
		module->SetID(id);                                        \
		module->SetName((char*)#name);                            \
		kernel->feature.RegisterModule(module);                   \
	}                                                             \
	~_Mod_##name() {                                              \
		kernel->feature.UnregisterModule(module);                 \
	}                                                             \
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
	#define EXPORT_SYMBOL_ALIAS(sym, name)                           \
	static struct _Sym_##name {                                      \
		_Sym_##name() {                                              \
			uint32_t symAddr = 0; marco_cast(sym, symAddr);          \
			kernel->symbol.Export(symAddr, #name);                   \
		}                                                            \
		~_Sym_##name() {                                             \
			kernel->symbol.Unexport(#name);                          \
		}                                                            \
	} const _sym_##name __attribute__((used,__section__(".symbols")))

	///Export symbol marco
	#define EXPORT_SYMBOL(symbol)          EXPORT_SYMBOL_ALIAS(symbol, symbol) 
#endif

#endif //!__DEFINES_H__
