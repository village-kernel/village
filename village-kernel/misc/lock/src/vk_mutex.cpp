//###########################################################################
// vk_mutex.cpp
// Definitions of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_mutex.h"
#include "vk_kernel.h"


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
    while (true == lock) { kernel->thread.Sleep(ticks); }
    lock = !lock;
}


/// @brief Mutex unlock
void Mutex::Unlock()
{
    lock = !lock;
}
