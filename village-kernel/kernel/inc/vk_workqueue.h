//###########################################################################
// vk_workqueue.h
// Declarations of the functions that manage work queue
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_WORK_QUEUE_H__
#define __VK_WORK_QUEUE_H__

#include "vk_workqueue.h"
#include "vk_kernel.h"
#include "vk_list.h"
#include "vk_cast.h"


/// @brief ConcreteWorkQueue
class ConcreteWorkQueue : public WorkQueue, public Class
{
private:
    /// @brief Members
    VkList<Work*> works;

    /// @brief Methods
    void Execute();
public:
    /// @brief Methods
    ConcreteWorkQueue();
    ~ConcreteWorkQueue();
    void Setup();
    void Exit();

    /// @brief Create Methods
    Work* Create(Function func, void* user = NULL, void* args = NULL, uint32_t ticks = 0);
    Work* Create(Method method, Class* user, void* args = NULL, uint32_t ticks = 0);

    /// @brief Feature Methods
    bool Delete(Work* work);
    bool Sched(Work* work);
};

#endif // !__VK_WORK_QUEUE_H__
