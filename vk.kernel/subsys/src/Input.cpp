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


/// @brief Input initialize
void Input::Initialize()
{

}


/// @brief Input execute
void Input::Execute()
{
	while (1) {}
}


/// @brief 
/// @param observer 
void Input::Attach(InputObserver* observer)
{
	observers.Add(observer);
}
EXPORT_SYMBOL(_ZN5Input6AttachEP13InputObserver);


/// @brief 
/// @param observer 
void Input::Detach(InputObserver* observer)
{
	observers.Remove(observer);
}
EXPORT_SYMBOL(_ZN5Input6DetachEP13InputObserver);


/// @brief 
void Input::Notify()
{
	for (observers.Begin(); !observers.IsEnd(); observers.Next())
	{
		observers.Item()->Update();
	}
}
EXPORT_SYMBOL(_ZN5Input6NotifyEv);


/// @brief 
/// @param keycode 
/// @param status 
void Input::ReportEvent(uint8_t keycode, int status)
{
	this->keycode = keycode;
	this->status  = status;
}
EXPORT_SYMBOL(_ZN5Input11ReportEventEhi);


/// @brief 
/// @param keycode 
/// @param status 
void Input::ReadEvent(uint8_t& keycode, int& status)
{
	keycode = this->keycode;
	status  = this->status;
}
EXPORT_SYMBOL(_ZN5Input9ReadEventERhRi);


/// @brief 
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Input::ReportMovement(int axisX, int axisY, int axisZ)
{
	this->axisX = axisX;
	this->axisY = axisY;
	this->axisZ = axisZ;
}
EXPORT_SYMBOL(_ZN5Input14ReportMovementEiii);


/// @brief 
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Input::ReadMovement(int& axisX, int& axisY, int& axisZ)
{
	axisX = this->axisX;
	axisY = this->axisY;
	axisZ = this->axisZ;
}
EXPORT_SYMBOL(_ZN5Input12ReadMovementERiS0_S0_);


///Register module
REGISTER_MODULE(new Input(), ModuleID::_input, input);
