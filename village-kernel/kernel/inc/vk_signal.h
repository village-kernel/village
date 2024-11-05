//###########################################################################
// vk_signal.h
// Declarations of the functions that manage signal
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SIGNAL_H__
#define __VK_SIGNAL_H__

#include "vk_kernel.h"
#include "vk_signals.h"


/// @brief ConcreteSignal
class ConcreteSignal : public Signal
{
public:
	/// @brief Methods
	ConcreteSignal();
	~ConcreteSignal();
	void Setup();
	void Exit();

	/// @brief Feature Methods
	void Raising(int signal);
};

#endif // !__VK_SIGNAL_H__
