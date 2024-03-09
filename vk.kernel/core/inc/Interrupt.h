//###########################################################################
// Interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "Component.h"


/// @brief Interrupt
class Interrupt : public Component
{
public:
	//Methods
	virtual int SetISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int SetISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int AppendISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual int RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL) = 0;
	virtual int RemoveISR(int irq, Method method, Class* user, void* args = NULL) = 0;
	virtual void ClearISR(int irq) = 0;
	virtual void Handler(int irq) = 0;
};

#endif //!__INTERRUPT_H__
