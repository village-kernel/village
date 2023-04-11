//###########################################################################
// Synchronize.cpp
// Definitions of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Synchronize.h"


/// @brief Mutex lock
void Mutex::Lock()
{

}


/// @brief Mutex unlock
void Mutex::Unlock()
{

}


/// @brief SpinLock lock
void SpinLock::Lock()
{

}


/// @brief SpinLock unlock
void SpinLock::Unlock()
{

}


/// @brief Semaphore set limit
/// @param limit 
void Semaphore::Set(int limit)
{
	this->limit = limit;
}


/// @brief Semaphore down
void Semaphore::Down()
{

}


/// @brief Semaphore up
void Semaphore::Up()
{

}
