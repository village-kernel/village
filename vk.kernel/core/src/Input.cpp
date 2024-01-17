//###########################################################################
// Input.cpp
// Definitions of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Input.h"
#include "Debug.h"
#include "Environment.h"


/// @brief Constructor
Input::Input()
{
}


/// @brief Destructor
Input::~Input()
{
}


/// @brief Singleton Instance
/// @return Input instance
Input& Input::Instance()
{
	static Input instance;
	return instance;
}
EXPORT_SYMBOL(_ZN5Input8InstanceEv);


/// @brief Definitions input
Input& input = Input::Instance();
EXPORT_SYMBOL(input);


/// @brief Input initialize
void Input::Initialize()
{

}


/// @brief Input execute
void Input::Execute()
{
	while (1) {}
}


/// @brief Attach event
/// @param func 
/// @param user 
void Input::AttachEvent(Function func, void* user)
{
	eventObservers.Add(new Observer(func, user));
}
EXPORT_SYMBOL(_ZN5Input11AttachEventEPFvPvS0_ES0_);


/// @brief Detach event
/// @param func 
/// @param user 
void Input::DetachEvent(Function func, void* user)
{
	for (eventObservers.Begin(); !eventObservers.IsEnd(); eventObservers.Next())
	{
		Observer* observer = eventObservers.Item();

		if ((func == observer->func) &&
			(user == observer->user))
		{
			eventObservers.Remove(observer, eventObservers.GetNid());
		}
	}
}
EXPORT_SYMBOL(_ZN5Input11DetachEventEPFvPvS0_ES0_);


/// @brief Attach movement
/// @param func 
/// @param user 
void Input::AttachMovement(Function func, void* user)
{
	moveObservers.Add(new Observer(func, user));
}
EXPORT_SYMBOL(_ZN5Input14AttachMovementEPFvPvS0_ES0_);


/// @brief Detach movement
/// @param func 
/// @param user 
void Input::DetachMovement(Function func, void* user)
{
	for (moveObservers.Begin(); !moveObservers.IsEnd(); moveObservers.Next())
	{
		Observer* observer = moveObservers.Item();

		if ((func == observer->func) &&
			(user == observer->user))
		{
			moveObservers.Remove(observer, moveObservers.GetNid());
		}
	}
}
EXPORT_SYMBOL(_ZN5Input14DetachMovementEPFvPvS0_ES0_);


/// @brief Notify event
void Input::NotifyEvent()
{
	for (eventObservers.Begin(); !eventObservers.IsEnd(); eventObservers.Next())
	{
		Observer* observer = eventObservers.Item();
		(observer->func)(observer->user, (void*)&inputEvent);
	}
}


/// @brief Notify movement
void Input::NotifyMovement()
{
	for (moveObservers.Begin(); !moveObservers.IsEnd(); moveObservers.Next())
	{
		Observer* observer = moveObservers.Item();
		(observer->func)(observer->user, (void*)&inputMove);
	}
}


/// @brief Report event
/// @param keycode 
/// @param status 
void Input::ReportEvent(uint8_t keycode, int status)
{
	inputEvent.keycode = keycode;
	inputEvent.status  = status;
	NotifyEvent();
}
EXPORT_SYMBOL(_ZN5Input11ReportEventEhi);


/// @brief 
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Input::ReportMovement(int axisX, int axisY, int axisZ)
{
	inputMove.axisX = axisX;
	inputMove.axisY = axisY;
	inputMove.axisZ = axisZ;
	NotifyMovement();
}
EXPORT_SYMBOL(_ZN5Input14ReportMovementEiii);


///Register module
REGISTER_MODULE(&Input::Instance(), ModuleID::_input, input);
