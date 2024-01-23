//###########################################################################
// Input.h
// Declarations of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"
#include "Templates.h"

/// @brief Input
class Input : public Module
{
public:
	//Enumerations
	enum Type
	{
		_Event = 0,
		_MoveMent,
		_AllType,
	};

	//Structures
	struct InputEvent
	{
		uint8_t keycode;
		int     status;

		InputEvent()
			:keycode(0),
			status(0)
		{}
	};

	struct InputMove
	{
		int axisX;
		int axisY;
		int axisZ;

		InputMove()
			:axisX(0),
			axisY(0),
			axisZ(0)
		{}
	};
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
	InputEvent      inputEvent;
	InputMove       inputMove;

	//Methods
	void Attach(List<Observer*>& observer, Function func, void* user = NULL);
	void Detach(List<Observer*>& observer, Function func, void* user = NULL);
	void Notify(List<Observer*>& observer, void* argv);
public:
	//Methods
	Input();
	~Input();
	void Attach(Type type, Method method, Class* user);
	void Attach(Type type, Function func, void* user = NULL);
	void Detach(Type type, Method method, Class* user);
	void Detach(Type type, Function func, void* user = NULL);
	void ReportEvent(uint8_t keycode, int status);
	void ReportMovement(int axisX, int axisY, int axisZ);
};

#endif //!__INPUT_H__
