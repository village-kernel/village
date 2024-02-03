//###########################################################################
// System.h
// A mostly static class containing system wide functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "Hardware.h"
#include "Module.h"

/// @brief System
class System : public Module
{
public:
	virtual uint32_t GetSysClkCounts() = 0;
	virtual void DelayMs(uint32_t millis) = 0;
	virtual void EnableIRQ() = 0;
	virtual void DisableIRQ() = 0;
	virtual void Reboot() = 0;
};

#endif //!__SYSTEM_H__
