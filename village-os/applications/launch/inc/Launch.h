//###########################################################################
// Launch.h
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LAUNCH_H__
#define __LAUNCH_H__

#include "Graphics.h"
#include "Kernel.h"


///Lanuch
class Launch : public Class
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;

	//Methods
	void UpdateInput(InputEvent::Loc* input);
public:
	//Methods
	Launch();
	~Launch();
	void Initialize(const char* screen, const char* keyboard, const char* mouse);
	void Execute();
};

#endif //!__LAUNCH_H__
