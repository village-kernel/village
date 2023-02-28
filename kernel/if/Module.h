//###########################################################################
// Module.h
// Specifies the interface for all classes that contain module logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"

///Module
class Module
{
private:
	//Members
	uint32_t ID;
public:
	//Methods
	virtual void Initialize()       {}
	virtual void Execute()          {}
	virtual void UpdateParams()     {}
	virtual void FailSafe(int arg)  {}

	///Set the module id
	inline void SetID(uint32_t id) { ID = id; }

	///Get the module id
	inline uint32_t GetID() { return ID; }
};

#endif // !__MODULE_INTERFACE_H__
