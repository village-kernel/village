//###########################################################################
// Signal.h
// Declarations of the functions that manage signal
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include "Kernel.h"
#include "Signals.h"


/// @brief ConcreteSignal
class ConcreteSignal : public Signal
{
public:
	//Methods
	ConcreteSignal();
	~ConcreteSignal();
	void Setup();
	void Exit();
	void Raising(int signal);
};

#endif // !__SIGNAL_H__
