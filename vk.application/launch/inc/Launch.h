//###########################################################################
// Launch.h
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LAUNCH_H__
#define __LAUNCH_H__

#include "Graphics.h"
#include "Village.h"
#include "Input.h"


///Lanuch
class Launch : public InputObserver
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;
	Village  village;

	int axisX;
	int axisY;
	int axisZ;
public:
	//Methods
	Launch();
	~Launch();
	void Initialize(const char* drvname);
	void Execute();
	void Update();
};

#endif //!__LAUNCH_H__
