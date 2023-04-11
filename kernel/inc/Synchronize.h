//###########################################################################
// Synchronize.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYNCHRONIZE_H__
#define __SYNCHRONIZE_H__

#include "Defines.h"


/// @brief Mutex
class Mutex
{
public:
	//Methods
	void Lock();
	void Unlock();
};


/// @brief SpinLock
class SpinLock
{
public:
	//Methods
	void Lock();
	void Unlock();
};


/// @brief Semaphore
class Semaphore
{
private:
	//Members
	int limit;
public:
	//Methods
	void Set(int limit);
	void Up();
	void Down();
};

#endif //!__SYNCHRONIZE_H__
