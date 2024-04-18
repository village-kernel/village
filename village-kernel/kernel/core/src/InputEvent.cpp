//###########################################################################
// Input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "InputEvent.h"


/// @brief Constructor
ConcreteInputEvent::ConcreteInputEvent()
{
}


/// @brief Desturctor
ConcreteInputEvent::~ConcreteInputEvent()
{
}


/// @brief InputEvent Setup
void ConcreteInputEvent::Setup()
{

}


/// @brief InputEvent Exit
void ConcreteInputEvent::Exit()
{
	for (int i = 0; i < _AllType; i++)
	{
		observers[i].Release();
	}		
}


/// @brief Input base attach
/// @param observer 
/// @param func 
/// @param user 
void ConcreteInputEvent::Attach(List<Observer*>& observers, Function func, void* user)
{
	observers.Add(new Observer(func, user));
}


/// @brief Input base detach
/// @param observer 
/// @param func 
/// @param user 
void ConcreteInputEvent::Detach(List<Observer*>& observers, Function func, void* user)
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
void ConcreteInputEvent::Notify(List<Observer*>& observers, void* argv)
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
void ConcreteInputEvent::Attach(Type type, Method method, Class* user)
{
	Attach(observers[type], union_cast<Function>(method), (void*)user);
}


/// @brief Input Attach
/// @param func 
/// @param user 
void ConcreteInputEvent::Attach(Type type, Function func, void* user)
{
	Attach(observers[type], func, user);
}


/// @brief Input Detach
/// @param method 
/// @param user 
void ConcreteInputEvent::Detach(Type type, Method method, Class* user)
{
	Detach(observers[type], union_cast<Function>(method), (void*)user);
}


/// @brief Input Detach
/// @param func 
/// @param user 
void ConcreteInputEvent::Detach(Type type, Function func, void* user)
{
	Detach(observers[type], func, user);
}


/// @brief Input report key
/// @param code 
/// @param status 
void ConcreteInputEvent::ReportKey(int code, int status)
{
	key.code = code;
	key.status = status;
	Notify(observers[_Key], (void*)&key);
}


/// @brief Input report location
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void ConcreteInputEvent::ReportLoc(int axisX, int axisY, int axisZ)
{
	loc.axisX = axisX;
	loc.axisY = axisY;
	loc.axisZ = axisZ;
	Notify(observers[_Loc], (void*)&loc);
}
