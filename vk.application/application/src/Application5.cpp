//###########################################################################
// Application5.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application5.h"
#include "VGA.h"


/// Constructor
Application5::Application5()
{
}


/// Initialize
void Application5::Initialize()
{
	Driver* display = device.GetDriver(DriverID::_display);
	gui.Initialize((VGA*)display);
	gui.disp.Printf("hello vk.kernel\r\n");

	interrupt.SetISR(33, union_cast<Function>(&Application5::ExtHandler), (char*)this);
	thread.CreateTaskCpp(this, (Method)&Application5::Test1);
	thread.CreateTaskCpp(this, (Method)&Application5::Test2);
}


/// Execute
void Application5::Execute()
{
	uint32_t test = 0;

	while (1)
	{
		test++;
		gui.disp.Printf("\nApplication5 Execute: %d", test);
		thread.Sleep(1000);
	}
}


void Application5::Test1()
{
	uint32_t test = 10;
	
	while (1)
	{
		test++;
		gui.disp.Printf("\nApplication5 Test1: %d", test);
		thread.Sleep(1000);
	}
}


void Application5::Test2()
{
	uint32_t test = 20;

	while (1)
	{
		test++;
		gui.disp.Printf("\nApplication5 Test2: %d", test);
		thread.Sleep(1000);
	}
}


///Ext handler
void Application5::ExtHandler()
{
	/* The PIC leaves us the scancode in port 0x60 */
	uint8_t scancode = PortByteIn(0x60);
	gui.disp.Printf("\nKeyboard scancode: %d,", scancode);
	PrintLetter(scancode);
}


void Application5::PrintLetter(uint8_t scancode)
{
    switch (scancode) {
        case 0x0:
            gui.disp.Printf((char*)"ERROR");
            break;
        case 0x1:
            gui.disp.Printf((char*)"ESC");
            break;
        case 0x2:
            gui.disp.Printf((char*)"1");
            break;
        case 0x3:
            gui.disp.Printf((char*)"2");
            break;
        case 0x4:
            gui.disp.Printf((char*)"3");
            break;
        case 0x5:
            gui.disp.Printf((char*)"4");
            break;
        case 0x6:
            gui.disp.Printf((char*)"5");
            break;
        case 0x7:
            gui.disp.Printf((char*)"6");
            break;
        case 0x8:
            gui.disp.Printf((char*)"7");
            break;
        case 0x9:
            gui.disp.Printf((char*)"8");
            break;
        case 0x0A:
            gui.disp.Printf((char*)"9");
            break;
        case 0x0B:
            gui.disp.Printf((char*)"0");
            break;
        case 0x0C:
            gui.disp.Printf((char*)"-");
            break;
        case 0x0D:
            gui.disp.Printf((char*)"+");
            break;
        case 0x0E:
            gui.disp.Printf((char*)"Backspace");
            break;
        case 0x0F:
            gui.disp.Printf((char*)"Tab");
            break;
        case 0x10:
            gui.disp.Printf((char*)"Q");
            break;
        case 0x11:
            gui.disp.Printf((char*)"W");
            break;
        case 0x12:
            gui.disp.Printf((char*)"E");
            break;
        case 0x13:
            gui.disp.Printf((char*)"R");
            break;
        case 0x14:
            gui.disp.Printf((char*)"T");
            break;
        case 0x15:
            gui.disp.Printf((char*)"Y");
            break;
        case 0x16:
            gui.disp.Printf((char*)"U");
            break;
        case 0x17:
            gui.disp.Printf((char*)"I");
            break;
        case 0x18:
            gui.disp.Printf((char*)"O");
            break;
        case 0x19:
            gui.disp.Printf((char*)"P");
            break;
		case 0x1A:
			gui.disp.Printf((char*)"[");
			break;
		case 0x1B:
			gui.disp.Printf((char*)"]");
			break;
		case 0x1C:
			gui.disp.Printf((char*)"ENTER");
			break;
		case 0x1D:
			gui.disp.Printf((char*)"LCtrl");
			break;
		case 0x1E:
			gui.disp.Printf((char*)"A");
			break;
		case 0x1F:
			gui.disp.Printf((char*)"S");
			break;
        case 0x20:
            gui.disp.Printf((char*)"D");
            break;
        case 0x21:
            gui.disp.Printf((char*)"F");
            break;
        case 0x22:
            gui.disp.Printf((char*)"G");
            break;
        case 0x23:
            gui.disp.Printf((char*)"H");
            break;
        case 0x24:
            gui.disp.Printf((char*)"J");
            break;
        case 0x25:
            gui.disp.Printf((char*)"K");
            break;
        case 0x26:
            gui.disp.Printf((char*)"L");
            break;
        case 0x27:
            gui.disp.Printf((char*)";");
            break;
        case 0x28:
            gui.disp.Printf((char*)"'");
            break;
        case 0x29:
            gui.disp.Printf((char*)"`");
            break;
		case 0x2A:
			gui.disp.Printf((char*)"LShift");
			break;
		case 0x2B:
			gui.disp.Printf((char*)"\\");
			break;
		case 0x2C:
			gui.disp.Printf((char*)"Z");
			break;
		case 0x2D:
			gui.disp.Printf((char*)"X");
			break;
		case 0x2E:
			gui.disp.Printf((char*)"C");
			break;
		case 0x2F:
			gui.disp.Printf((char*)"V");
			break;
        case 0x30:
            gui.disp.Printf((char*)"B");
            break;
        case 0x31:
            gui.disp.Printf((char*)"N");
            break;
        case 0x32:
            gui.disp.Printf((char*)"M");
            break;
        case 0x33:
            gui.disp.Printf((char*)",");
            break;
        case 0x34:
            gui.disp.Printf((char*)".");
            break;
        case 0x35:
            gui.disp.Printf((char*)"/");
            break;
        case 0x36:
            gui.disp.Printf((char*)"Rshift");
            break;
        case 0x37:
            gui.disp.Printf((char*)"Keypad *");
            break;
        case 0x38:
            gui.disp.Printf((char*)"LAlt");
            break;
        case 0x39:
            gui.disp.Printf((char*)"Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                gui.disp.Printf((char*)"Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                gui.disp.Printf((char*)"key up ");
                PrintLetter(scancode - 0x80);
            } else gui.disp.Printf((char*)"Unknown key up");
            break;
    }
}


///Register module
REGISTER_MODULE(new Application5(), (ModuleID::_application + 5), app_5);
