//###########################################################################
// ArchInterrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ARCH_INTERRUPT_H__
#define __ARCH_INTERRUPT_H__

#include "Module.h"


/// @brief Interrupt
class ArchInterrupt : public Module
{
public:
	//Static constants
	static const uint32_t isr_num = 256;
	static const uint32_t rsvd_isr_size = 16;
};

#endif //!__INTERRUPT_H__
