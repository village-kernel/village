//###########################################################################
// InputEvent.h
// Declarations of the functions that manage input event
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_EVENT_H__
#define __INPUT_EVENT_H__

#include "ObserverModel.h"
#include "Kernel.h"
#include "List.h"
#include "Cast.h"


/// @brief ConcreteInputEvent
class ConcreteInputEvent : public InputEvent
{
private:
	/// @brief Input members
	InputKey     inputKey;
	InputAxis    inputAxis;
	
	/// @brief Output members
	OutputText   outputText;
	OutputAxis   outputAxis;
	OutFormat    outFormat;

	/// @brief Model members
	ObserverModel observers[_AllType];
public:
	/// @brief Methods
	ConcreteInputEvent();
	~ConcreteInputEvent();
	void Setup();
	void Exit();

	/// @brief Attach Methods
	void Attach(EventType type, Method method, Class* user);
	void Attach(EventType type, Function func, void* user = NULL);
	void Detach(EventType type, Method method, Class* user);
	void Detach(EventType type, Function func, void* user = NULL);
	
	/// @brief Input Methods
	void ReportKey(int code, int status);
	void ReportAxis(int axisX, int axisY, int axisZ);

	/// @brief Output Methods
	void PushChar(char chr);
	void PushString(char* data, int size);
	void PushAxis(int axisX, int axisY, int axisZ);
	void SetOutFormat(OutFormat format);
	OutFormat GetOutFormat();
};

#endif //!__INPUT_EVENT_H__
