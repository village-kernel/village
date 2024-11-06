//###########################################################################
// vk_module.h
// Specifies the interface for all classes that contain module logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MODULE_INTERFACE_H__
#define __VK_MODULE_INTERFACE_H__

#include "vk_defines.h"
#include "vk_class.h"


/// @brief Module
class Module : public Base, public Class
{
public:
	//Constructor
	Module() { }

	//Destructor
	virtual ~Module() { }

	//Methods
	virtual bool  Setup() = 0;
	virtual void  Exit()  = 0;
	virtual void  SetData(void* data) { }
	virtual void* GetData() { return NULL; }
};

#endif // !__VK_MODULE_INTERFACE_H__
