//###########################################################################
// vk_semaphore.cpp
// Definitions of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_semaphore.h"
#include "vk_kernel.h"


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
	while(0 > counter) { kernel->thread.Sleep(ticks); }
}


/// @brief Semaphore up
void Semaphore::Up()
{
	counter++; if (counter > limit) counter = limit;
}
