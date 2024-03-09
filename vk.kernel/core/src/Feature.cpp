//###########################################################################
// Feature.cpp
// Definitions of the functions that manage component object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Feature.h"
#include "Kernel.h"
#include "List.h"


/// @brief ConcreteFeature
class ConcreteFeature : public Feature
{
private:
	//Members
	bool isRuntime;
	List<Component*> components;
private:
	/// @brief Register in runtime
	/// @param component 
	void RegisterInRuntime(Component* component)
	{
		if (isRuntime) component->Setup();
	}


	/// @brief Deregister in runtime
	/// @param component 
	void DeregisterInRuntime(Component* component)
	{
		if (isRuntime) component->Exit();
	}


	/// @brief Register components
	void RegisterComponents()
	{
		extern ComponentInfo __components_start;
		extern ComponentInfo __components_end;

		uint32_t count = &__components_end - &__components_start;
		ComponentInfo* components = &__components_start;

		for (uint32_t i = 0; i < count; i++)
		{
			components[i].body->SetID(components[i].id);
			components[i].body->SetName(components[i].name);
			RegisterComponent(components[i].body);
		}
	}
public:
	/// @brief Constructor
	ConcreteFeature()
		:isRuntime(false)
	{
	}


	/// @brief Destructor
	~ConcreteFeature()
	{
	}


	/// @brief Execute component object->Setup
	void Setup()
	{
		isRuntime = false;

		RegisterComponents();
		
		for (components.Begin(); !components.IsEnd(); components.Next())
		{
			Component* component = components.Item();

			if (ComponentID::_feature != component->GetID())
			{
				component->Setup();
			}
		}

		isRuntime = true;
	}


	/// @brief Execute component object->Exit
	void Exit()
	{
		for (components.Begin(); !components.IsEnd(); components.Next())
		{
			Component* component = components.Item();

			if (ComponentID::_feature != component->GetID())
			{
				component->Exit();
			}
		}
	}


	/// @brief Register component object
	/// @param component component pointer
	void RegisterComponent(Component* component)
	{
		components.Insert(component, component->GetID(), component->GetName());
		RegisterInRuntime(component);
	}


	/// @brief Deregister component object
	/// @param component component pointer
	void DeregisterComponent(Component* component)
	{
		DeregisterInRuntime(component);
		components.Remove(component);
	}


	/// @brief Get the component object
	/// @param id component id
	/// @return component
	Component* GetComponent(uint32_t id)
	{
		return components.GetItem(id);
	}


	/// @brief Get the component object by name
	/// @param name component name
	/// @return driver
	Component* GetComponent(const char* name)
	{
		return components.GetItemByName(name);
	}
}; 


///Register component
REGISTER_COMPONENT(ConcreteFeature, ComponentID::_feature, feature);
