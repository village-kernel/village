//###########################################################################
// vg_input.h
// Declarations of the functions that manage input
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INPUT_H__
#define __VG_INPUT_H__

#include "vg_devices.h"
#include "vg_indev.h"
#include "vg_list.h"


/// @brief GraphicsInput
class GraphicsInput
{
private:
	//Members
	GraphicsDevices& devices;
	VgList<Indev*>   indevs;
	bool             isReady;
public:
	//Methods
	GraphicsInput(GraphicsDevices& devices);
	~GraphicsInput();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	void RegisterIndev(Indev* indev);
	void UnregisterIndev(Indev* indev);
};

#endif //!__VG_INPUT_H__
