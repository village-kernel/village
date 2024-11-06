//###########################################################################
// vk_mutex.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MUTEX_H__
#define __VK_MUTEX_H__

#include "vk_defines.h"


/// @brief Mutex
class Mutex
{
private:
	//Members
	volatile bool lock;
	volatile int  ticks;
public:
	//Methods
	Mutex(int ticks = 1);
	~Mutex();
	void Lock();
	void Unlock();
};

#endif //!__VK_MUTEX_H__
