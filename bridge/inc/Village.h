//###########################################################################
// Village.h
// Declarations of the functions that manage village
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VILLAGE_H__
#define __VILLAGE_H__

#include "Defines.h"
#include "Driver.h"

/// @brief Village
class Village
{
public:
	//Methods
	Village();
	~Village();

	void Sleep(uint32_t ticks);

	uint32_t GetMemSize();
	uint32_t GetMemUsed();

	Driver* GetDriver(uint32_t id);
	Driver* GetDriverByName(const char* name);

	void SetDebugLevel(int level);

	//Singleton Instance
	static Village& Instance();
};

///Declarations Village reference
extern Village& village;

#endif //!__VILLAGE_H__
