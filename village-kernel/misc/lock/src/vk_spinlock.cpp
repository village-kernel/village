//###########################################################################
// vk_spinlock.cpp
// Definitions of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_spinlock.h"


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
