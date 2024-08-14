//###########################################################################
// PS2KeyBoard.cpp
// Definitions of the functions that manage key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Hardware.h"
#include "EventCodes.h"


/// @brief PS2KeyBoard
class PS2KeyBoard : public Driver
{
private:
	//Scan code set 1
	const int keyCodes[0x59] = {
		/* 0x00 */ _KeyReserved,   _KeyESC,   _Key1,         _Key2,           _Key3,       _Key4,        _Key5,          _Key6, 
		/* 0x08 */ _Key7,          _Key8,     _Key9,         _Key0,          _KeyMinus,    _KeyEqual,    _KeyBackSpace,  _KeyTab,
		/* 0x10 */ _KeyQ,          _KeyW,     _KeyE,         _KeyR,          _KeyT,        _KeyY,        _KeyU,          _KeyI,
		/* 0x18 */ _KeyO,          _KeyP,     _KeyLeftBrace, _KeyRightBrace, _KeyEnter,    _KeyLeftCtrl, _KeyA,          _KeyS,
		/* 0x20 */ _KeyD,          _KeyF,     _KeyG,         _KeyH,          _KeyJ,        _KeyK,        _KeyL,          _KeySemicolon,
		/* 0x28 */ _KeyApostrophe, _KeyGrave, _KeyLeftShift, _KeyBackSlash,  _KeyZ,        _KeyX,        _KeyC,          _KeyV,
		/* 0x30 */ _KeyB,          _KeyN,     _KeyM,         _KeyComma,      _KeyDot,      _KeySlash,    _KeyRightShift, _KeyKPAsterisk,
		/* 0x38 */ _KeyLeftAlt,    _KeySpace, _KeyCapsLock,  _KeyF1,         _KeyF2,       _KeyF3,       _KeyF4,         _KeyF5,
		/* 0x40 */ _KeyF6,         _KeyF7,    _KeyF8,        _KeyF9,         _KeyF10,      _KeyNumLock,  _KeyScrollLock, _KeyKP7,
		/* 0x48 */ _KeyKP8,        _KeyKP9,   _KeyKPMinus,   _KeyKP4,        _KeyKP5,      _KeyKP6,      _KeyKPPlus,     _KeyKP1,
		/* 0x50 */ _KeyKP2,        _KeyKP3,   _KeyKP0,       _KeyKPDot,      _KeyReserved, _KeyReserved, _KeyReserved,   _KeyF11,
		/* 0x58 */ _KeyF12
	};

	//Extende scan code set 1
	const int extendeKeyCodes[0x58] = {
		/* 0x00 */ _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved,
		/* 0x08 */ _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved,
		/* 0x10 */ _KeyBack,     _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved,
		/* 0x18 */ _KeyReserved, _KeyForward,   _KeyReserved, _KeyReserved, _KeyKPEnter,  _KeyRightCtrl, _KeyReserved, _KeyReserved,
		/* 0x20 */ _KeyMute,     _KeyReserved,  _KeyPlay,     _KeyReserved, _KeyStop,     _KeyReserved,  _KeyReserved, _KeyReserved,
		/* 0x28 */ _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyVolumeDown,
		/* 0x30 */ _KeyVolumeUp, _KeyReserved,  _KeyWWW,      _KeyReserved, _KeyReserved, _KeyKPSlash,   _KeyReserved, _KeyReserved,
		/* 0x38 */ _KeyRightAlt, _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved,
		/* 0x40 */ _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved, _KeyReserved, _KeyReserved,  _KeyReserved, _KeyHome,
		/* 0x48 */ _KeyUp,       _KeyPageUp,    _KeyReserved, _KeyLeft,     _KeyReserved, _KeyRight,     _KeyReserved, _KeyEnd,
		/* 0x50 */ _KeyDown,     _KeyPageDown,  _KeyInsert,   _KeyDelete,   _KeyReserved, _KeyReserved,  _KeyReserved, _KeyReserved,
	};
private:
	//Members
	bool isExtended;
private:
	/// @brief Interrupt handler
	void InputHandler()
	{
		if (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)
		{
			//Get the raw scancode
			int scancode = PortByteIn(PS2_READ_DATA);
			
			//Set the isExtended flag and return when scancode is 0xE0
			if (0xE0 == scancode) { isExtended = true; return; }
			
			//Select keycodes table
			const int* pKeyCodes = isExtended ? extendeKeyCodes : keyCodes;

			//Report key event
			if (scancode > 0 && scancode <= 0x58)
				kernel->inputEvent.ReportKey(pKeyCodes[scancode], _KeyPressed);
			else if (scancode > 0x80 && scancode <= 0xd8)
				kernel->inputEvent.ReportKey(pKeyCodes[scancode - 0x80], _KeyReleased);
	
			//Clear the isExtended flag
			isExtended = false;
		}
	}
public:
	/// @brief Constructor
	PS2KeyBoard()
		:isExtended(false)
	{
	}


	/// @brief Destructor
	~PS2KeyBoard()
	{
	}


	/// @brief KeyBoard open
	bool Open()
	{
		kernel->interrupt.SetISR(Keyboard_Controller_IRQn, (Method)(&PS2KeyBoard::InputHandler), this);
		return true;
	}


	/// @brief KeyBoard close
	void Close()
	{
		kernel->interrupt.RemoveISR(Keyboard_Controller_IRQn, (Method)(&PS2KeyBoard::InputHandler), this);
	}
};


//Register driver
REGISTER_DRIVER(new PS2KeyBoard(), DriverID::_character, ps2keyboard);
