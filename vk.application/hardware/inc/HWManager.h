//###########################################################################
// HWManager.h
// Declarations of the functions that manage hardware device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_MANAGER_H__
#define __HW_MANAGER_H__

#include "Module.h"
#include "ILI9488.h"

///HWManager
class HWManager : public Module
{
private:
	//Static members
	static HWManager instance;

	//Methods
	HWManager();
	void ILI9488Initialize();
public:
	//Members
	ILI9488 ili9488;

	//Methods
	void Initialize();
	void UpdateParams();
	void FailSafe(int arg);

	///Gets the singleton instance of HWManager
	static inline HWManager* Instance() { return &instance; }
};

#endif // !__HW_MANAGER_H__
