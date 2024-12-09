//###########################################################################
// vk_observer.h
// Declarations of the functions that manage observer model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_OBSERVER_H__
#define __VK_OBSERVER_H__

#include "vk_kernel.h"
#include "vk_list.h"
#include "vk_cast.h"


/// @brief ObserverModel
class ObserverModel
{
protected:
	//Structures
	struct Observer
	{
		Function    func;
		void*       user;

		Observer(Function func = NULL, void* user = NULL)
			:func(func),
			user(user)
		{}
	};

	//Members
	VkList<Observer*> observers;
public:
	//Methods
	ObserverModel();
	virtual ~ObserverModel();
	virtual void Attach(Method method, Class* user);
	virtual void Attach(Function func, void* user = NULL);
	virtual void Detach(Method method, Class* user);
	virtual void Detach(Function func, void* user = NULL);
	virtual void Notify(void* argv);
	virtual void Release();
};

#endif //!__VK_OBSERVER_H__
