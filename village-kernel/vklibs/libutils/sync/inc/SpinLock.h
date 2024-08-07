//###########################################################################
// SpinLock.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SPIN_LOCK_H__
#define __SPIN_LOCK_H__

#include "Defines.h"

/// @brief SpinLock
class SpinLock
{
private:
	//Members
	volatile bool lock;
public:
	//Methods
	SpinLock();
	~SpinLock();
	void Lock();
	void Unlock();
};

#endif //!__SPIN_LOCK_H__
