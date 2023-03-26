//###########################################################################
// ThreadEndPoint.h
// Declarations of the functions that manage thread end point
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_END_POINT_H__
#define __THREAD_END_POINT_H__

#include "Thread.h"

//ThreadEndPoint class template 
template<typename User, typename Handler>
class ThreadEndPoint
{
private:
	//Declarations static members
	static User* user;
	static Handler handler;
	
	//Thread Handler
	static inline void TaskHandler()
	{
		if (user != 0) { (user->*handler)(); }
	}
public:
	//Set task end point and create task
	static inline void CreateTask(User* _user, Handler _handler)
	{
		user = _user;
		handler = _handler;
		Thread::CreateTask(ThreadEndPoint::TaskHandler);
	}
};

//Definitions static members
template<typename User, typename Handler>
User* ThreadEndPoint<User, Handler>::user;
template<typename User, typename Handler>
Handler ThreadEndPoint<User, Handler>::handler;

#endif //!__THREAD_END_POINT_H__
