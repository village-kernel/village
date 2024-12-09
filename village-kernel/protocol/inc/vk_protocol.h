//###########################################################################
// vk_protocol.h
// Declarations of the functions that manage protocol stack
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PROTOCOL_H__
#define __VK_PROTOCOL_H__

#include "vk_kernel.h"
#include "vk_stack.h"
#include "vk_list.h"


/// @brief ConcreteProtocol
class ConcreteProtocol : public Protocol
{
private:
	/// @brief Members
	bool isRuntime;
	VkList<Stack*> stacks;
public:
	/// @brief Methods
	ConcreteProtocol();
	~ConcreteProtocol();
	void Setup();
	void Exit();

	/// @brief Register Methods
	void RegisterStack(Stack* stack);
	void UnregisterStack(Stack* stack);
};

#endif // !__VK_PROTOCOL_H__
