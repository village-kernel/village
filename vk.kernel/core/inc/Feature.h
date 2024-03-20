//###########################################################################
// Feature.h
// Declarations of the functions that manage component object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FEATURE_H__
#define __FEATURE_H__

#include "Component.h"


/// @brief Feature
class Feature : public Component
{
public:
	//Methods
	virtual void RegisterComponent(Component* component) = 0;
	virtual void DeregisterComponent(Component* component) = 0;
	virtual Component* GetComponent(uint32_t id) = 0;
	virtual Component* GetComponent(const char* name) = 0;
};

#endif // !__FEATURE_H__
