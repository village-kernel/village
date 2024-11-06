//###########################################################################
// vk_protocol.cpp
// Definitions of the functions that manage protocol stack
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_protocol.h"


/// @brief Constructor
ConcreteProtocol::ConcreteProtocol()
{
}


/// @brief Destructor
ConcreteProtocol::~ConcreteProtocol()
{
}


/// @brief Setup
void ConcreteProtocol::Setup()
{
	isRuntime = false;
		
	for (stacks.Begin(); !stacks.IsEnd(); stacks.Next())
	{
		stacks.Item()->Setup();
	}

	isRuntime = true;

	//Output debug info
	kernel->debug.Info("Protocol setup done!");
}


/// @brief Exit
void ConcreteProtocol::Exit()
{
	isRuntime = false;
	stacks.Release();
}


/// @brief RegisterStack
/// @param stack 
void ConcreteProtocol::RegisterStack(Stack* stack)
{
	stacks.Add(stack, stack->GetName());
	if (isRuntime) stack->Setup();
}


/// @brief UnregisterStack
/// @param stack 
void ConcreteProtocol::UnregisterStack(Stack* stack)
{
	if (isRuntime) stack->Exit();
	stacks.Remove(stack);
}
