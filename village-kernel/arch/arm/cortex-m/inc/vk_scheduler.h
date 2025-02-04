//###########################################################################
// vk_scheduler.h
// Declarations of the functions that manage thread scheduler
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SCHEDULER_H__
#define __VK_SCHEDULER_H__

#include "vk_kernel.h"


/// @brief Scheduler
class ConcreteScheduler : public Scheduler, public Class
{
private:
    /// @brief Members
    bool isStartSchedule;

    /// @brief Methods
    void SysTickHandler();

    /// @brief Static Methods
    static void PendSVHandler();
public:
    /// @brief Methods
    ConcreteScheduler();
    ~ConcreteScheduler();
    void Setup();
    void Exit();
    void Start();
    void Sched();
};

#endif // !__VK_SCHEDULER_H__
