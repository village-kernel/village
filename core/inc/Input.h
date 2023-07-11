//###########################################################################
// Input.h
// Declarations of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"

/// @brief Input
class Input : public Module
{
private:
	//Methods
	Input();
	~Input();
public:
	//Methods
	void Initialize();
	void Execute();
	void ReportKey(uint8_t keycode, int status);

	//Singleton Instance
	static Input& Instance();
};

///Declarations input reference
extern Input& input;

#endif //!__INPUT_H__
