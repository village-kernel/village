//###########################################################################
// Module.h
// Specifies the interface for all classes that contain module logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "System.h"

///Module layer id definition
constexpr auto HARDWARE_ID_START = 0U;
constexpr auto MISC_DEV_ID_START = 256U;
constexpr auto FUNCTION_ID_START = 512U;
constexpr auto COMM_APP_ID_START = 768U;
constexpr auto EXTENDED_ID_START = 1024U;

///Module layer id macro
template<typename T>
constexpr auto HARDWARE_ID(T id) { return (HARDWARE_ID_START + id); }
template<typename T>
constexpr auto MISC_DEV_ID(T id) { return (MISC_DEV_ID_START + id); }
template<typename T>
constexpr auto FUNCTION_ID(T id) { return (FUNCTION_ID_START + id); }
template<typename T>
constexpr auto COMM_APP_ID(T id) { return (COMM_APP_ID_START + id); }
template<typename T>
constexpr auto EXTENDED_ID(T id) { return (EXTENDED_ID_START + id); }

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
