//###########################################################################
// Interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "stdint.h"
#include "stddef.h"

///Interrupt end point
class InterruptEndpoint {};
typedef void (InterruptEndpoint::*InterruptHandlerCpp)();
typedef void (*InterruptHandlerC)();


//Interrupt
class Interrupt
{
public:
	void SetISR(int irq, InterruptHandlerC handler);
};

#endif //!__INTERRUPT_H__
