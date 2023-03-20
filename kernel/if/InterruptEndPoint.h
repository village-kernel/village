//###########################################################################
// InterruptEndPoint.h
// Declarations of the functions that manage interrupt end point
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_END_POINT_H__
#define __INTERRUPT_END_POINT_H__

#include "Interrupt.h"

//InterruptEndPoint class template 
template<typename User, typename Handler>
class InterruptEndPoint
{
private:
	//Declarations static members
	static User* user;
	static Handler handler;
	
	//ISR Handler
	static inline void ISRHandler()
	{
		if (user != 0) { (user->*handler)(); }
	}
public:
	//Set interrupt end point
	static inline void SetISR(int _irq, User* _user, Handler _handler)
	{
		user = _user;
		handler = _handler;
		Interrupt::SetISR(_irq, InterruptEndPoint::ISRHandler);
	}
};

//Definitions static members
template<typename User, typename Handler>
User* InterruptEndPoint<User, Handler>::user;
template<typename User, typename Handler>
Handler InterruptEndPoint<User, Handler>::handler;

#endif //!__INTERRUPT_END_POINT_H__
