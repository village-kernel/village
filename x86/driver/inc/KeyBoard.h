//###########################################################################
// KeyBoard.h
// Declarations of the functions that manage key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KEY_BOARD_H__
#define __KEY_BOARD_H__

#include "Driver.h"
#include "WorkQueue.h"

/// @brief KeyBoard
class KeyBoard : public Driver
{
private:
	//Members
	uint8_t keycode;
	WorkQueue::Work* work;
	
	//Methods
	void InputHandler();
	void ReportHandler();
public:
	//Methods
	KeyBoard();
	~KeyBoard();
	void Initialize();
	void Exit();
};

#endif //! __KEY_BOARD_H__
