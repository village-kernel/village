//###########################################################################
// Bridge.h
// Declarations of the functions that manage bridge
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "Defines.h"
#include "Driver.h"

/// @brief Bridge
class Bridge
{
public:
	//Methods
	Bridge();
	~Bridge();
	Driver* GetDriver(uint32_t id);
	Driver* GetDriverByName(const char* name);
};

#endif //!__BRIDGE_H__
