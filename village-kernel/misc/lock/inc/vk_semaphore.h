//###########################################################################
// vk_semaphore.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SEMAPHORE_H__
#define __VK_SEMAPHORE_H__

#include "vk_defines.h"


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

#endif //!__VK_SEMAPHORE_H__
 