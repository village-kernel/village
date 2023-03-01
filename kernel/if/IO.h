//###########################################################################
// IO.h
// Specifies the interface for all classes that contain input output logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_OUTPUT_INTERFACE_H__
#define __INPUT_OUTPUT_INTERFACE_H__

#include "Defines.h"

///IO
class IO
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

	//IO ctrl methods
	virtual int Write(uint8_t* data, uint32_t size, uint32_t offset) { return 0; }
	virtual int Read(uint8_t* data, uint32_t size, uint32_t offset)  { return 0; }

	///Set the input/output id
	inline void SetID(uint32_t id) { ID = id; }

	///Get the input/output id
	inline uint32_t GetID() { return ID; }
};

#endif // !__INPUT_OUTPUT_INTERFACE_H__
