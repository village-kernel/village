//###########################################################################
// vk_symbol.h
// Declarations of the functions that manage symbol object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_SYMBOL_H__
#define __VK_SYMBOL_H__

#include "vk_kernel.h"
#include "vk_list.h"


/// @brief ConcreteSymbol
class ConcreteSymbol : public Symbol
{
private:
	/// @brief Structures
	struct Entry
	{
		const char* name;
		uint32_t    addr;

		Entry(const char* name, uint32_t addr):
			name(name),
			addr(addr)
		{}
	};

	/// @brief Members
	VkList<Entry*> entrys;
public:
	/// @brief Methods
	ConcreteSymbol();
	~ConcreteSymbol();
	void Setup();
	void Exit();

	/// @brief Methods
	void Export(uint32_t symAddr, const char* name);
	void Unexport(const char* name);
	uint32_t Search(const char* name);
};

#endif //!__VK_SYMBOL_H__
