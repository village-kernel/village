//###########################################################################
// Registers.h
// Declarations of the arch registers
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#if defined(ARCH_ARM)
#include "Registers-ARM.h"
#elif defined(ARCH_X86)
#include "Registers-x86.h"
#endif

#endif //!__REGISTERS_H__
