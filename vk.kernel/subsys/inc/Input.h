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


/// @brief Input observer
class InputObserver
{
public:
	//Methods
	//virtual ~InputObserver() {}
	virtual void Update() = 0;
};


/// @brief Input
class Input : public Module
{
protected:
	//Members
	uint8_t keycode;
	int     status;
	int     axisX;
	int     axisY;
	int     axisZ;

	//Members
	List<InputObserver*> observers;
public:
	//Methods
	Input();
	~Input();
	void Initialize();
	void Execute();

	void Attach(InputObserver* observer);
	void Detach(InputObserver* observer);
	void Notify();

	void ReportEvent(uint8_t keycode, int status);
	void ReadEvent(uint8_t& keycode, int& status);

	void ReportMovement(int axisX, int axisY, int axisZ);
	void ReadMovement(int& axisX, int& axisY, int& axisZ);
};

#endif //!__INPUT_H__
