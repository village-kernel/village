//###########################################################################
// SyncLock.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYNC_LOCK_H__
#define __SYNC_LOCK_H__

#include "Defines.h"


/// @brief SpinLock
class SpinLock
{
private:
	//Members
	bool lock;
public:
	//Methods
	SpinLock();
	~SpinLock();
	void Lock();
	void Unlock();
};


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


/// @brief Semaphore
class Semaphore
{
private:
	//Members
	int limit;
	int counter;
	int ticks;
public:
	//Methods
	Semaphore(int limit = 1, int ticks = 1);
	~Semaphore();
	void Up();
	void Down();
};

#endif //!__SYNC_LOCK_H__
