//###########################################################################
// ObserverModel.h
// Declarations of the functions that manage observer model
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __OBSERVER_MODEL_H__
#define __OBSERVER_MODEL_H__

#include "Kernel.h"
#include "List.h"
#include "Cast.h"


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
	List<Observer*> observers;
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

#endif //!__OBSERVER_MODEL_H__
