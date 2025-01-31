//###########################################################################
// vk_event_codes.h
// Declarations of the interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_EVENT_CODES_H__
#define __VK_EVENT_CODES_H__

/*
 * Keys and buttons
 *
 * Most of the keys/buttons are modeled after USB HUT 1.12
 * (see http://www.usb.org/developers/hidpage).
 * Abbreviations in the comments:
 * AC - Application Control
 * AL - Application Launch Button
 * SC - System Control
 */

enum EventCode
{
    _KeyReserved             = 0,
    _KeyESC                  = 1,
    _Key1                    = 2,
    _Key2                    = 3,
    _Key3                    = 4,
    _Key4                    = 5,
    _Key5                    = 6,
    _Key6                    = 7,
    _Key7                    = 8,
    _Key8                    = 9,
    _Key9                    = 10,
    _Key0                    = 11,
    _KeyMinus                = 12, /* '-' */
    _KeyEqual                = 13, /* '=' */
    _KeyBackSpace            = 14,
    _KeyTab                  = 15,
    _KeyQ                    = 16,
    _KeyW                    = 17,
    _KeyE                    = 18,
    _KeyR                    = 19,
    _KeyT                    = 20,
    _KeyY                    = 21,
    _KeyU                    = 22,
    _KeyI                    = 23,
    _KeyO                    = 24,
    _KeyP                    = 25,
    _KeyLeftBrace            = 26, /* '[' */
    _KeyRightBrace           = 27, /* ']' */
    _KeyEnter                = 28,
    _KeyLeftCtrl             = 29,
    _KeyA                    = 30,
    _KeyS                    = 31,
    _KeyD                    = 32,
    _KeyF                    = 33,
    _KeyG                    = 34,
    _KeyH                    = 35,
    _KeyJ                    = 36,
    _KeyK                    = 37,
    _KeyL                    = 38,
    _KeySemicolon            = 39, /* ';' */
    _KeyApostrophe           = 40, /* ''' */
    _KeyGrave                = 41, /* '`' */
    _KeyLeftShift            = 42,
    _KeyBackSlash            = 43, /* '\' */
    _KeyZ                    = 44,
    _KeyX                    = 45,
    _KeyC                    = 46,
    _KeyV                    = 47,
    _KeyB                    = 48,
    _KeyN                    = 49,
    _KeyM                    = 50,
    _KeyComma                = 51, /* ',' */
    _KeyDot                  = 52, /* '.' */
    _KeySlash                = 53, /* '/' */
    _KeyRightShift           = 54,
    _KeyKPAsterisk           = 55, /* '*' */
    _KeyLeftAlt              = 56,
    _KeySpace                = 57,
    _KeyCapsLock             = 58,
    _KeyF1                   = 59,
    _KeyF2                   = 60,
    _KeyF3                   = 61,
    _KeyF4                   = 62,
    _KeyF5                   = 63,
    _KeyF6                   = 64,
    _KeyF7                   = 65,
    _KeyF8                   = 66,
    _KeyF9                   = 67,
    _KeyF10                  = 68,
    _KeyNumLock              = 69,
    _KeyScrollLock           = 70,
    _KeyKP7                  = 71,
    _KeyKP8                  = 72,
    _KeyKP9                  = 73,
    _KeyKPMinus              = 74, /* '-' */
    _KeyKP4                  = 75,
    _KeyKP5                  = 76,
    _KeyKP6                  = 77,
    _KeyKPPlus               = 78, /* '+' */
    _KeyKP1                  = 79,
    _KeyKP2                  = 80,
    _KeyKP3                  = 81,
    _KeyKP0                  = 82,
    _KeyKPDot                = 83,
    _KeyZenkakuHankaku       = 84,

    _Key102ND                = 86,
    _KeyF11                  = 87,
    _KeyF12                  = 88,
    _KeyRO                   = 89,
    _KeyKatakana             = 90,
    _KeyHiragana             = 91,
    _KeyHenkan               = 92,
    _KeyKatakanaHiragana     = 93,
    _KeyMuhenkan             = 94,
    _KeyKPJPcomma            = 95, /* ',' */
    _KeyKPEnter              = 96,
    _KeyRightCtrl            = 97,
    _KeyKPSlash              = 98, /* '/' */
    _KeySysrq                = 99,
    _KeyRightAlt             = 100,
    _KeyLineFeed             = 101,
    _KeyHome                 = 102,
    _KeyUp                   = 103,
    _KeyPageUp               = 104,
    _KeyLeft                 = 105,
    _KeyRight                = 106,
    _KeyEnd                  = 107,
    _KeyDown                 = 108,
    _KeyPageDown             = 109,
    _KeyInsert               = 110,
    _KeyDelete               = 111,
    _KeyMacro                = 112,
    _KeyMute                 = 113,
    _KeyVolumeDown           = 114,
    _KeyVolumeUp             = 115,
    _KeyPower                = 116, /* SC System Power Down */
    _KeyKPEqual              = 117,
    _KeyKPPlusMinus          = 118,
    _KeyPause                = 119,
    _KeyScale                = 120, /* AL Compiz Scale (Expose) */

    _KeyKPComma              = 121, /* ',' */
    _KeyHangeul              = 122,
    _KeyHanguel              = _KeyHangeul,
    _KeyHanja                = 123,
    _KeyYen                  = 124,
    _KeyLeftMeta             = 125,
    _KeyRightMeta            = 126,
    _KeyCompose              = 127,

    _KeyStop                 = 128, /* AC Stop */
    _KeyAgain                = 129,
    _KeyProps                = 130, /* AC Properties */
    _KeyUndo                 = 131, /* AC Undo */
    _KeyFront                = 132,
    _KeyCopy                 = 133, /* AC Copy */
    _KeyOpen                 = 134, /* AC Open */
    _KeyPaste                = 135, /* AC Paste */
    _KeyFind                 = 136, /* AC Search */
    _KeyCut                  = 137, /* AC Cut */
    _KeyHelp                 = 138, /* AL Integrated Help Center */
    _KeyMenu                 = 139, /* Menu (show menu) */
    _KeyCalc                 = 140, /* AL Calculator */
    _KeySetup                = 141,
    _KeySleep                = 142, /* SC System Sleep */
    _KeyWakeup               = 143, /* System Wake Up */
    _KeyFile                 = 144, /* AL Local Machine Browser */
    _KeySendFile             = 145,
    _KeyDeleteFile           = 146,
    _KeyXFER                 = 147,
    _KeyProg1                = 148,
    _KeyProg2                = 149,
    _KeyWWW                  = 150, /* AL Internet Browser */
    _KeyMSDOS                = 151, 
    _KeyCoffee               = 152, /* AL Terminal Lock/Screen saver */
    _KeyScreenLock           = _KeyCoffee,
    _KeyRotateDisplay        = 153, /* Display orientation for e.g. tablets */
    _KeyDirection            = _KeyRotateDisplay,
    _KeyCycleWindows         = 154,
    _KeyMail                 = 155,
    _KeyBookMarks            = 156, /* AC Bookmarks */
    _KeyComputer             = 157,
    _KeyBack                 = 158, /* AC Back */
    _KeyForward              = 159, /* AC Forward */
    _KeyCloseCD              = 160,
    _KeyEjectCD              = 161,
    _KeyEjectCloseCD         = 162,
    _KeyNextSong             = 163,
    _KeyPlayPause            = 164,
    _KeyPreviousSong         = 165,
    _KeyStopCD               = 166,
    _KeyRecord               = 167,
    _KeyRewind               = 168,
    _KeyPhone                = 169, /* Media Select Telephone */
    _KeyISO                  = 170,
    _KeyConfig               = 171, /* AL Consumer Control Configuration */
    _KeyHomePage             = 172, /* AC Home */
    _KeyRefresh              = 173, /* AC Refresh */
    _KeyExit                 = 174, /* AC Exit */
    _KeyMove                 = 175,
    _KeyEdit                 = 176,
    _KeyScrollUp             = 177,
    _KeyScrollDown           = 178,
    _KeyKPLeftParen          = 179,
    _KeyKPRightParen         = 180,
    _KeyNew                  = 181, /* AC New */
    _KeyRedo                 = 182, /* AC Redo/Repeat */

    _KeyF13                  = 183,
    _KeyF14                  = 184,
    _KeyF15                  = 185,
    _KeyF16                  = 186,
    _KeyF17                  = 187,
    _KeyF18                  = 188,
    _KeyF19                  = 189,
    _KeyF20                  = 190,
    _KeyF21                  = 191,
    _KeyF22                  = 192,
    _KeyF23                  = 193,
    _KeyF24                  = 194,

    _KeyPlayCD               = 200,
    _KeyPauseCD              = 201,
    _KeyProg3                = 202,
    _KeyProg4                = 203,
    _KeyAllApplications      = 204,    /* AC Desktop Show All Applications */
    _KeyDashboard            = _KeyAllApplications,
    _KeySuspend              = 205,
    _KeyClose                = 206, /* AC Close */
    _KeyPlay                 = 207,
    _KeyFastForward          = 208,
    _KeyBassBoost            = 209,
    _KeyPrint                = 210, /* AC Print */
    _KeyHP                   = 211,
    _KeyCamera               = 212,
    _KeySound                = 213,
    _KeyQuestion             = 214,
    _KeyEmail                = 215,
    _KeyChat                 = 216,
    _KeySearch               = 217,
    _KeyConnect              = 218,
    _KeyFinance              = 219, /* AL Checkbook/Finance */
    _KeySport                = 220,
    _KeyShop                 = 221,
    _KeyAlterase             = 222,
    _KeyCancel               = 223, /* AC Cancel */
    _KeyBrightnessDown       = 224,
    _KeyBrightnessUp         = 225,
    _KeyMedia                = 226,
    
    _KeySwitchVideoMode      = 227, /* Cycle between available video outputs (Monitor/LCD/TV-out/etc) */
    _KeyKBDillumToggle       = 228,
    _KeyKBDillumDown         = 229,
    _KeyKBDillumUp           = 230,

    _KeySend                 = 231, /* AC Send */
    _KeyReply                = 232, /* AC Reply */
    _KeyForwardMail          = 233, /* AC Forward Msg */
    _KeySave                 = 234, /* AC Save */
    _KeyDocuments            = 235,

    _KeyBattery              = 236,

    _KeyBluetooth            = 237,
    _KeyWlan                 = 238,
    _KeyUWB                  = 239,
    
    _KeyUnknow               = 240,
    
    _KeyVideoNext            = 241, /* drive next video source */
    _KeyVideoPrev            = 242, /* drive previous video source */
    _KeyBrightnessCycle      = 243, /* brightness up, after max is min */
    _KeyBrightnessAuto       = 244, /* Set Auto Brightness: manual brightness control is off, rely on ambient */
    _KeyBrightnessZero       = _KeyBrightnessAuto,
    _KeyDisplayOff           = 245, /* display device to off state */
    _KeyWWAN                 = 246, /* Wireless WAN (LTE, UMTS, GSM, etc.) */
    _KeyWIMAX                = _KeyWWAN,
    _KeyRFKill               = 247, /* Key that controls all radios */
    _KeyMicMute              = 248, /* Mute / unmute the microphone */

    _BtnMouse                = 0x110,
    _BtnLeft                 = 0x110,
    _BtnRight                = 0x111,
    _BtnMiddle               = 0x112,
    _BtnSide                 = 0x113,
    _BtnExtra                = 0x114,
    _BtnForward              = 0x115,
    _BtnBack                 = 0x116,
    _BtnTask                 = 0x117,
};

enum KeyStatus
{
    _KeyReleased = 0,
    _KeyPressed,
};

#endif //!__VK_EVENT_CODES_H__
