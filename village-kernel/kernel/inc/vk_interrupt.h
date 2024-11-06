//###########################################################################
// vk_interrupt.h
// Declarations of the functions that manage interrupt
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_INTERRUPT_H__
#define __VK_INTERRUPT_H__

#include "vk_kernel.h"
#include "vk_list.h"
#include "vk_cast.h"
#include "vk_exception.h"


/// @brief ConcreteInterrupt
class ConcreteInterrupt : public Interrupt
{
private:
	/// @brief Structures
	struct Isr
	{
		int32_t     irq;
		Function    func;
		void*       user;
		void*       args;

		Isr(int32_t irq = 0, Function func = NULL, void* user = NULL, void* args = NULL)
			:irq(irq),
			func(func),
			user(user),
			args(args)
		{}
	};

	/// @brief Static constants
	static const uint32_t warning_times = 10;

	/// @brief Members
	volatile bool isReady;
	Exception     exception;
	uint8_t       warnings[Exception::isr_num] = { 0 };
	List<Isr*>    isrTabs[Exception::isr_num];
public:
	/// @brief Methods
	ConcreteInterrupt();
	~ConcreteInterrupt();
	void Setup();
	void Exit();

	/// @brief Set Methods
	int SetISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int SetISR(int irq, Method method, Class* user, void* args = NULL);

	/// @brief Append Methods
	int AppendISR(int irq, Function func, void* user = NULL, void* args = NULL);
	int AppendISR(int irq, Method method, Class* user, void* args = NULL);
	
	/// @brief Remove Methods
	bool RemoveISR(int irq, Function func, void* user = NULL, void* args = NULL);
	bool RemoveISR(int irq, Method method, Class* user, void* args = NULL);
	
	/// @brief Clear Methods
	void ClearISR(int irq);
	
	/// @brief Replace Methods
	void Replace(int irq, uint32_t handler);
	
	/// @brief Feature Methods
	void Handler(int irq);
};

#endif //!__VK_INTERRUPT_H__
