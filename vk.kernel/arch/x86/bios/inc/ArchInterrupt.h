//###########################################################################
// ArchInterrupt.h
// Declarations of the functions that manage arch interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ARCH_INTERRUPT_H__
#define __ARCH_INTERRUPT_H__

#include "Component.h"


/// @brief ArchInterrupt
class ArchInterrupt : public Component
{
public:
	//Static constants
	static const uint32_t isr_num = 256;
public:
	//Methods
	virtual uint16_t GetPicIrqReg(int ocw3) = 0;
	virtual uint16_t GetPicIrr() = 0;
	virtual uint16_t GetPicIsr() = 0;
};

#endif //!__ARCH_INTERRUPT_H__
