//###########################################################################
// InputEvent.h
// Declarations of the functions that manage input event
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_EVENT_H__
#define __INPUT_EVENT_H__

#include "Kernel.h"
#include "List.h"
#include "Cast.h"


/// @brief ConcreteInputEvent
class ConcreteInputEvent : public InputEvent
{
private:
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
	Key key;
	Loc loc;
	List<Observer*> observers[_AllType];

	//Methods
	void Attach(List<Observer*>& observers, Function func, void* user);
	void Detach(List<Observer*>& observers, Function func, void* user);
	void Notify(List<Observer*>& observers, void* argv);
public:
	//Methods
	ConcreteInputEvent();
	~ConcreteInputEvent();
	void Setup();
	void Exit();
	void Attach(Type type, Method method, Class* user);
	void Attach(Type type, Function func, void* user = NULL);
	void Detach(Type type, Method method, Class* user);
	void Detach(Type type, Function func, void* user = NULL);
	void ReportKey(int code, int status);
	void ReportLoc(int axisX, int axisY, int axisZ);
};

#endif //!__INPUT_EVENT_H__
