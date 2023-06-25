//###########################################################################
// SyncLock.cpp
// Definitions of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "SyncLock.h"
#include "Thread.h"


/// @brief SpinLock constructor
SpinLock::SpinLock()
	:lock(false)
{
}


/// @brief SpinLock deconstructor
SpinLock::~SpinLock()
{
}


/// @brief SpinLock lock
void SpinLock::Lock()
{
	while (true == lock) {}
	lock = !lock;
}


/// @brief SpinLock unlock
void SpinLock::Unlock()
{
	lock = !lock;
}


/// @brief Mutex constructor
Mutex::Mutex(int ticks)
	:lock(false),
	ticks(ticks)
{
}


/// @brief Mutex deconstructor
Mutex::~Mutex()
{
}


/// @brief Mutex lock
void Mutex::Lock()
{
	while (true == lock) { thread.Sleep(ticks); }
	lock = !lock;
}


/// @brief Mutex unlock
void Mutex::Unlock()
{
	lock = !lock;
}


/// @brief Semaphore constructor
/// @param limit 
Semaphore::Semaphore(int limit, int ticks)
	:limit(limit),
	counter(limit),
	ticks(ticks)
{
}


/// @brief Semaphore deconstructor
Semaphore::~Semaphore()
{
}


/// @brief Semaphore down
void Semaphore::Down()
{
	if (counter >= 0) counter--; 
	while(0 > counter) { thread.Sleep(ticks); }
}


/// @brief Semaphore up
void Semaphore::Up()
{
	counter++; if (counter > limit) counter = limit;
}
