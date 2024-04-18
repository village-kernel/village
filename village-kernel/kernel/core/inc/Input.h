//###########################################################################
// Input.h
// Declarations of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_H__
#define __INPUT_H__

#include "Kernel.h"
#include "List.h"
#include "Cast.h"


/// @brief ConcreteInput
class ConcreteInput : public Input
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
	List<Observer*> observers[_AllType];
	Event           event;
	Movement        movement;

	//Methods
	void Attach(List<Observer*>& observers, Function func, void* user);
	void Detach(List<Observer*>& observers, Function func, void* user);
	void Notify(List<Observer*>& observers, void* argv);
public:
	//Methods
	ConcreteInput();
	~ConcreteInput();
	void Setup();
	void Exit();
	void Attach(Type type, Method method, Class* user);
	void Attach(Type type, Function func, void* user = NULL);
	void Detach(Type type, Method method, Class* user);
	void Detach(Type type, Function func, void* user = NULL);
	void ReportEvent(int keycode, int status);
	void ReportMovement(int axisX, int axisY, int axisZ);
};

#endif //!__INPUT_H__
