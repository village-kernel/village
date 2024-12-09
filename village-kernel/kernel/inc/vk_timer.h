//###########################################################################
// vk_timer.h
// Declarations of the functions that manage timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TIMER_H__
#define __VK_TIMER_H__

#include "vk_kernel.h"
#include "vk_timer.h"
#include "vk_list.h"
#include "vk_cast.h"


/// @brief ConcreteTimer
class ConcreteTimer : public Timer, public Class
{
private:
	/// @brief Members
	System*      system;
	VkList<Job*> jobs;
	
	/// @brief Methods
	void Execute();
public:
	/// @brief Methods
	ConcreteTimer();
	~ConcreteTimer();
	void Setup();
	void Exit();

	/// @brief Create Methods
	Job* Create(uint32_t ticks, Function func, void* user = NULL, void* args = NULL);
	Job* Create(uint32_t ticks, Method method, Class* user, void* args = NULL);

	/// @brief Feature Methods
	void Modify(Job* job, uint32_t ticks);
	bool Delete(Job* job);
};

#endif // !__VK_TIMER_H__
