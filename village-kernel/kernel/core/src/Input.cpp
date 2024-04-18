//###########################################################################
// Input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Input.h"


/// @brief Constructor
ConcreteInput::ConcreteInput()
{
}


/// @brief Desturctor
ConcreteInput::~ConcreteInput()
{
}


/// @brief Input Setup
void ConcreteInput::Setup()
{

}


/// @brief Input Exit
void ConcreteInput::Exit()
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
void ConcreteInput::Attach(List<Observer*>& observers, Function func, void* user)
{
	observers.Add(new Observer(func, user));
}


/// @brief Input base detach
/// @param observer 
/// @param func 
/// @param user 
void ConcreteInput::Detach(List<Observer*>& observers, Function func, void* user)
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
void ConcreteInput::Notify(List<Observer*>& observers, void* argv)
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
void ConcreteInput::Attach(Type type, Method method, Class* user)
{
	Attach(observers[type], union_cast<Function>(method), (void*)user);
}


/// @brief Input Attach
/// @param func 
/// @param user 
void ConcreteInput::Attach(Type type, Function func, void* user)
{
	Attach(observers[type], func, user);
}


/// @brief Input Detach
/// @param method 
/// @param user 
void ConcreteInput::Detach(Type type, Method method, Class* user)
{
	Detach(observers[type], union_cast<Function>(method), (void*)user);
}


/// @brief Input Detach
/// @param func 
/// @param user 
void ConcreteInput::Detach(Type type, Function func, void* user)
{
	Detach(observers[type], func, user);
}


/// @brief Input report event
/// @param keycode 
/// @param status 
void ConcreteInput::ReportEvent(int keycode, int status)
{
	event.keycode = keycode;
	event.status  = status;
	Notify(observers[_Event], (void*)&event);
}


/// @brief Input report movement
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void ConcreteInput::ReportMovement(int axisX, int axisY, int axisZ)
{
	movement.axisX = axisX;
	movement.axisY = axisY;
	movement.axisZ = axisZ;
	Notify(observers[_Movement], (void*)&movement);
}
