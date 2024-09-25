//###########################################################################
// Protocol.h
// Declarations of the functions that manage protocol stack
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "Kernel.h"
#include "Stack.h"
#include "List.h"


/// @brief ConcreteProtocol
class ConcreteProtocol : public Protocol
{
private:
	/// @brief Members
	bool isRuntime;
	List<Stack*> stacks;
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

#endif // !__PROTOCOL_H__
