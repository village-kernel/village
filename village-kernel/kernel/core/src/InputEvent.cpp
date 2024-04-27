//###########################################################################
// InputEvent.cpp
// Definitions of the functions that manage input event
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
	outFormat = _Noraml;
}


/// @brief InputEvent Exit
void ConcreteInputEvent::Exit()
{
	for (int i = 0; i < _AllType; i++)
	{
		observers[i].Release();
	}
}


/// @brief Input attach
/// @param method 
/// @param user 
void ConcreteInputEvent::Attach(EventType type, Method method, Class* user)
{
	observers[type].Attach(method, user);
}


/// @brief Input Attach
/// @param func 
/// @param user 
void ConcreteInputEvent::Attach(EventType type, Function func, void* user)
{
	observers[type].Attach(func, user);
}


/// @brief Input Detach
/// @param method 
/// @param user 
void ConcreteInputEvent::Detach(EventType type, Method method, Class* user)
{
	observers[type].Detach(method, user);
}


/// @brief Input Detach
/// @param func 
/// @param user 
void ConcreteInputEvent::Detach(EventType type, Function func, void* user)
{
	observers[type].Detach(func, user);
}


/// @brief Input report key
/// @param code 
/// @param status 
void ConcreteInputEvent::ReportKey(int code, int status)
{
	inputKey.code = code;
	inputKey.status = status;
	observers[_InputKey].Notify((void*)&inputKey);
}


/// @brief Input report location
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void ConcreteInputEvent::ReportAxis(int axisX, int axisY, int axisZ)
{
	inputAxis.axisX = axisX;
	inputAxis.axisY = axisY;
	inputAxis.axisZ = axisZ;
	observers[_InputAxis].Notify((void*)&inputAxis);
}


/// @brief Input PushText
/// @param data 
/// @param size 
void ConcreteInputEvent::PushText(char* data, int size)
{
	outputText.data = data;
	outputText.size = size;
	observers[_OutputText].Notify((void*)&outputText);
}


/// @brief Input PushAxis
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void ConcreteInputEvent::PushAxis(int axisX, int axisY, int axisZ)
{
	outputAxis.axisX = axisX;
	outputAxis.axisY = axisY;
	outputAxis.axisZ = axisZ;
	observers[_OutputAxis].Notify((void*)&outputAxis);
}


/// @brief Input SetOutFormat
/// @param format 
void ConcreteInputEvent::SetOutFormat(OutFormat format)
{
	this->outFormat = format;
}


/// @brief Input GetOutFormat
/// @return 
ConcreteInputEvent::OutFormat ConcreteInputEvent::GetOutFormat()
{
	return outFormat;
}
