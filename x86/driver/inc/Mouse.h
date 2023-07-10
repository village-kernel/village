//###########################################################################
// Mouse.h
// Declarations of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Driver.h"
#include "WorkQueue.h"

/// @brief Mouse
class Mouse : public Driver
{
private:
	//Structures
	union Flags
	{
		struct
		{
			uint8_t yOverflow:1;
			uint8_t xOverflow:1;
			uint8_t ySignBit:1;
			uint8_t xSignBit:1;
			uint8_t always1:1;
			uint8_t middleBtn:1;
			uint8_t RightBtn:1;
			uint8_t LeftBtn:1;
		} __attribute__((packed)) bits;
		uint8_t byte;
	};

	//Members
	Flags flags;
	uint8_t x;
	uint8_t y;
	WorkQueue::Work* work;
	
	//Methods
	void InputHandler();
	void ReportHandler();
public:
	//Methods
	Mouse();
	~Mouse();
	void Initialize();
	void Exit();
};

#endif //! __MOUSE_H__
