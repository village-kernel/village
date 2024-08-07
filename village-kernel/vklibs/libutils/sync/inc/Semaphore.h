//###########################################################################
// Semaphore.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "Defines.h"

/// @brief Semaphore
class Semaphore
{
private:
	//Members
	volatile int limit;
	volatile int counter;
	volatile int ticks;
public:
	//Methods
	Semaphore(int limit = 1, int ticks = 1);
	~Semaphore();
	void Up();
	void Down();
};

#endif //!__SEMAPHORE_H__
 