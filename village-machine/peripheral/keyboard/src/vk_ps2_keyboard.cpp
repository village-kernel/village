//###########################################################################
// vk_ps2_keyboard.cpp
// Definitions of the functions that manage key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_ps2_keyboard.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"


//Scan code set 1
static const int keyCodes[0x59] = {
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
static const int extendeKeyCodes[0x58] = {
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


/// @brief Constructor
PS2KeyBoard::PS2KeyBoard()
    :isExtended(false)
{
}


/// @brief Destructor
PS2KeyBoard::~PS2KeyBoard()
{
}


/// @brief Set data
/// @param data 
void PS2KeyBoard::SetData(void* data)
{
    config = *((Config*)data);
}


/// @brief Interrupt handler
void PS2KeyBoard::InputHandler()
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
            kernel->event.ReportKey(pKeyCodes[scancode], _KeyPressed);
        else if (scancode > 0x80 && scancode <= 0xd8)
            kernel->event.ReportKey(pKeyCodes[scancode - 0x80], _KeyReleased);

        //Clear the isExtended flag
        isExtended = false;
    }
}


/// @brief KeyBoard open
bool PS2KeyBoard::Open()
{
    kernel->interrupt.SetISR(config.irq, (Method)(&PS2KeyBoard::InputHandler), this);
    return true;
}


/// @brief KeyBoard close
void PS2KeyBoard::Close()
{
    kernel->interrupt.RemoveISR(config.irq, (Method)(&PS2KeyBoard::InputHandler), this);
}


/// @brief Probe
/// @param device 
/// @return 
bool PS2KeyBoardDrv::Probe(PlatDevice* device)
{
    PS2KeyBoard* ps2keyboard = new PS2KeyBoard(); 
    ps2keyboard->SetID(DriverID::_input);
    ps2keyboard->SetName(device->GetDriverName());
    ps2keyboard->SetData(device->GetDriverData());
    device->SetDriver(ps2keyboard);
    kernel->device.RegisterInputDevice((InputDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool PS2KeyBoardDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterInputDevice((InputDriver*)device->GetDriver());
    delete (PS2KeyBoard*)device->GetDriver();
    device->SetDriver(NULL);
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new PS2KeyBoardDrv(), ps2keyboard, ps2keyboardDrv);
