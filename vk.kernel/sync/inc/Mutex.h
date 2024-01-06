//###########################################################################
// Mutex.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "Defines.h"

/// @brief Mutex
class Mutex
{
private:
	//Members
	bool lock;
	int  ticks;
public:
	//Methods
	Mutex(int ticks = 1);
	~Mutex();
	void Lock();
	void Unlock();
};

#endif //!__MUTEX_H__
