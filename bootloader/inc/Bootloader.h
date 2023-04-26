//###########################################################################
// Bootloader.h
// Declarations of the functions that manage bootloader
//
// $Copyright: Copyright (C) LDO Systems
//###########################################################################
#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "Module.h"

///Bootloader
class Bootloader : public Module
{
private:
public:
	Bootloader();
	void Initialize();
	void Execute();
};

#endif //!__BOOT_LOADER_H__
