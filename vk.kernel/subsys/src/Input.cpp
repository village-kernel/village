//###########################################################################
// Input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Input.h"
#include "Kernel.h"


/// @brief Constructor
Input::Input()
{
}


/// @brief Destructor
Input::~Input()
{
}


/// @brief Input base attach
/// @param observer 
/// @param func 
/// @param user 
void Input::Attach(List<Observer*>& observers, Function func, void* user)
{
	observers.Add(new Observer(func, user));
}


/// @brief Input base detach
/// @param observer 
/// @param func 
/// @param user 
void Input::Detach(List<Observer*>& observers, Function func, void* user)
{
	for (observers.Begin(); !observers.IsEnd(); observers.Next())
	{
		Observer* observer = observers.Item();

		if ((func == observer->func) &&
			(user == observer->user))
		{
			observers.Remove(observer, observers.GetNid());
		}
	}
}


/// @brief Input base notify
/// @param observer 
/// @param argv 
void Input::Notify(List<Observer*>& observers, void* argv)
{
	for (observers.Begin(); !observers.IsEnd(); observers.Next())
	{
		Observer* observer = observers.Item();
		(observer->func)(observer->user, argv);
	}
}


/// @brief Input attach
/// @param method 
/// @param user 
void Input::Attach(Type type, Method method, Class* user)
{
	Attach(observers[type], union_cast<Function>(method), (void*)user);
}
EXPORT_SYMBOL(_ZN5Input6AttachENS_4TypeEM5ClassFvPvEPS1_);


/// @brief Input Attach
/// @param func 
/// @param user 
void Input::Attach(Type type, Function func, void* user)
{
	Attach(observers[type], func, user);
}
EXPORT_SYMBOL(_ZN5Input6AttachENS_4TypeEPFvPvS1_ES1_);


/// @brief Input Detach
/// @param method 
/// @param user 
void Input::Detach(Type type, Method method, Class* user)
{
	Detach(observers[type], union_cast<Function>(method), (void*)user);
}
EXPORT_SYMBOL(_ZN5Input6DetachENS_4TypeEM5ClassFvPvEPS1_);


/// @brief Input Detach
/// @param func 
/// @param user 
void Input::Detach(Type type, Function func, void* user)
{
	Detach(observers[type], func, user);
}
EXPORT_SYMBOL(_ZN5Input6DetachENS_4TypeEPFvPvS1_ES1_);


/// @brief Input report event
/// @param keycode 
/// @param status 
void Input::ReportEvent(uint8_t keycode, int status)
{
	inputEvent.keycode = keycode;
	inputEvent.status  = status;
	Notify(observers[_Event], (void*)&inputEvent);
}
EXPORT_SYMBOL(_ZN5Input11ReportEventEhi);


/// @brief Input report movement
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Input::ReportMovement(int axisX, int axisY, int axisZ)
{
	inputMove.axisX = axisX;
	inputMove.axisY = axisY;
	inputMove.axisZ = axisZ;
	Notify(observers[_MoveMent], (void*)&inputMove);
}
EXPORT_SYMBOL(_ZN5Input14ReportMovementEiii);


///Register module
REGISTER_MODULE(new Input(), ModuleID::_input, input);
