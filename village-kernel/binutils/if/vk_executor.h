//###########################################################################
// vk_executor.h
// Specifies the interface for all classes that contain executor logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_EXECUTOR_INTERFACE_H__
#define __VK_EXECUTOR_INTERFACE_H__

#include "vk_execdefs.h"
#include "vk_class.h"
#include "vk_list.h"


/// @brief BaseExecutor
class BaseExecutor;


/// @brief Executor
class Executor
{
public:
	//Constructor
	Executor() { }

	//Destructor
	virtual ~Executor() { }

	//Methods
	virtual VkList<char*> GetSuffixes() = 0;
	virtual BaseExecutor* Create() = 0;
};

#endif // !__VK_EXECUTOR_INTERFACE_H__
