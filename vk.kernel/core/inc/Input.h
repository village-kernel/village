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
	List<Observer*> eventObservers;
	List<Observer*> moveObservers;
	InputEvent      inputEvent;
	InputMove       inputMove;

	//Methods
	Input();
	~Input();
	void NotifyEvent();
	void NotifyMovement();
public:
	//Methods
	void Initialize();
	void Execute();

	void AttachEvent(Function func, void* user = NULL);
	void DetachEvent(Function func, void* user = NULL);

	void AttachMovement(Function func, void* user = NULL);
	void DetachMovement(Function func, void* user = NULL);

	void ReportEvent(uint8_t keycode, int status);
	void ReportMovement(int axisX, int axisY, int axisZ);

	//Singleton Instance
	static Input& Instance();
};

///Declarations input reference
extern Input& input;

#endif //!__INPUT_H__
