//###########################################################################
// InterruptEndpoint.h
//
// Parent class that represents all classes which have member functions
// to be used as ISR functions.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INTERRUPT_END_POINT_H__
#define __INTERRUPT_END_POINT_H__

class InterruptEndpoint
{
};

typedef void (InterruptEndpoint::*InterruptMemberFunc)();

#endif //!__INTERRUPT_END_POINT_H__
