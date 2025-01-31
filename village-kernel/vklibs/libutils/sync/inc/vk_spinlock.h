//###########################################################################
// vk_spinlock.h
// Declarations of the functions that manage synchronization mechanism
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SPIN_LOCK_H__
#define __VK_SPIN_LOCK_H__

#include "vk_defines.h"


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

#endif //!__VK_SPIN_LOCK_H__
