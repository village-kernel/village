//###########################################################################
// IOStream.h
// Declarations of the functions that manage input output object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __IO_STREAM_H__
#define __IO_STREAM_H__

#include "IO.h"

///io create macro
#define CREATE_IO(io, name) static struct _IO_##name{_IO_##name(){io;}} const _io_##name;

///io register macro
#define REGISTER_IO(io, id, name) CREATE_IO(IOMgr::RegisterIO(io, id), name)

///IOStream
class IOStream
{
private:
	//Structures
	struct IONode
	{
		IO* io;
		IONode* next;

		IONode(IO* io = NULL) :
			io(io),
			next(NULL)
		{}
	};

	//Members
	static IONode* list;
public:
	//Methods
	IOStream();
	static void Initialize();
	static void UpdateParams();
	static void Execute();
	static void FailSafe(int arg);
	static int Write(uint8_t* data, uint16_t size = 0);
	static int Read(uint8_t* data, uint16_t size = 0);
	static void RegisterIO(IO* io, uint32_t id);
	static void DeregisterIO(IO* io, uint32_t id);
};

#endif // !__IO_STREAM_H__
