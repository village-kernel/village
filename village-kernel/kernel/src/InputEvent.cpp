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
	//Get all input devices
	List<Base*> devices = kernel->device.GetDevices(DriverID::_input);

	//Init all input devices
	for (devices.Begin(); !devices.IsEnd(); devices.Next())
	{
		InitInputDevice(devices.Item()->GetName());
	}

	//Set default output format
	outFormat = _Noraml;

	//Output debug info
	kernel->debug.Info("Input event setup done!");
}


/// @brief InputEvent Exit
void ConcreteInputEvent::Exit()
{
	//Get all input devices
	List<Base*> devices = kernel->device.GetDevices(DriverID::_input);

	//Exit all input devices
	for (devices.End(); !devices.IsBegin(); devices.Prev())
	{
		ExitInputDevice(devices.Item()->GetName());
	}

	//Release all input devices
	inDevs.Release();

	//Release all observers
	for (int i = 0; i < _AllType; i++)
	{
		observers[i].Release();
	}
}


/// @brief Init Input Device
/// @param input 
void ConcreteInputEvent::InitInputDevice(const char* input)
{
	//Create an input device object
	DevStream* device = new DevStream();
	
	//Open and add into inDevs list
	if (device->Open(input, FileMode::_Read))
	{
		inDevs.Add(device, (char*)input);
	}
}


/// @brief Exit Input Device
/// @param input 
void ConcreteInputEvent::ExitInputDevice(const char* input)
{
	//Gets the input device from inDevs list
	DevStream* device = inDevs.GetItem(input);
	
	//Close and remove from inDevs list
	if (NULL != device)
	{
		device->Close();
		inDevs.Remove(device);
		delete device;
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


/// @brief Input PushChar
/// @param data 
/// @param size 
void ConcreteInputEvent::PushChar(char chr)
{
	static char data[2] = {0}; data[0] = chr;
	outputText.data = data;
	outputText.size = 1;
	observers[_OutputText].Notify((void*)&outputText);
}


/// @brief Input PushString
/// @param data 
/// @param size 
void ConcreteInputEvent::PushString(char* data, int size)
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
