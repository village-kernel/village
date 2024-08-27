//###########################################################################
// PS2KeyBoard.h
// Declarations of the functions that manage ps2 key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __PS2_KEY_BOARD_H__
#define __PS2_KEY_BOARD_H__

#include "Hardware.h"
#include "Driver.h"


/// @brief PS2KeyBoard
class PS2KeyBoard : public CharDriver, public Class
{
public:
	//Structures
	struct Config
	{
		uint32_t irq;
	};
private:
	//Members
	Config config;
	bool isExtended;

	/// @brief Methods
	void InputHandler();
public:
	/// @brief Methods
	PS2KeyBoard();
	~PS2KeyBoard();

	/// @brief Plat Methods
	void SetData(void* data);

	/// @brief Fopts Methods
	bool Open();
	void Close();
};


/// @brief PS2KeyBoardDrv
class PS2KeyBoardDrv : public PlatDriver
{
public:
	/// @brief Plat Methods
	bool Probe(PlatDevice* device);
	bool Remove(PlatDevice* device);
};

#endif //!__PS2_KEY_BOARD_H__
