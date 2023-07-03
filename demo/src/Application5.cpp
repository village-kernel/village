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
	gui.Printf("hello vk.kernel\r\n");

	interrupt.SetISR(IRQ_Keyboard_Controller, union_cast<Function>(&Application5::ExtHandler), (char*)this);
	work = workQueue.Create(union_cast<Function>(&Application5::PrintLetter), (char*)this, work_delay);

	test1Pid = thread.CreateTask(this, (Method)&Application5::Test1);
	test2Pid = thread.CreateTask(this, (Method)&Application5::Test2);
}


/// Execute
void Application5::Execute()
{
	uint32_t test = 0;

	while (1)
	{
		test++;
		gui.Printf("\nApplication5 Execute: %d", test);
		thread.Sleep(1000);
	}
}


/// @brief Exit
void Application5::Exit()
{
	thread.DeleteTask(test1Pid);
	thread.DeleteTask(test2Pid);
	workQueue.Delete(work);
	interrupt.ClearISR(IRQ_Keyboard_Controller);
}


/// @brief Test1
void Application5::Test1()
{
	uint32_t test = 10;
	
	while (1)
	{
		test++;
		gui.Printf("\nApplication5 Test1: %d", test);
		thread.Sleep(1000);
	}
}


/// @brief Test2
void Application5::Test2()
{
	uint32_t test = 20;

	while (1)
	{
		test++;
		gui.Printf("\nApplication5 Test2: %d", test);
		thread.Sleep(1000);
	}
}


/// @brief Interrupt handler
void Application5::ExtHandler()
{
	/* The PIC leaves us the scancode in port 0x60 */
	keycode = PortByteIn(0x60);
	workQueue.Schedule(work);
}


/// @brief WorkQueun handler
void Application5::PrintLetter()
{
	gui.Printf("\nKeyboard scancode: %d,", keycode);

    switch (keycode) {
        case 0x0:
            gui.Printf((char*)"ERROR");
            break;
        case 0x1:
            gui.Printf((char*)"ESC");
            break;
        case 0x2:
            gui.Printf((char*)"1");
            break;
        case 0x3:
            gui.Printf((char*)"2");
            break;
        case 0x4:
            gui.Printf((char*)"3");
            break;
        case 0x5:
            gui.Printf((char*)"4");
            break;
        case 0x6:
            gui.Printf((char*)"5");
            break;
        case 0x7:
            gui.Printf((char*)"6");
            break;
        case 0x8:
            gui.Printf((char*)"7");
            break;
        case 0x9:
            gui.Printf((char*)"8");
            break;
        case 0x0A:
            gui.Printf((char*)"9");
            break;
        case 0x0B:
            gui.Printf((char*)"0");
            break;
        case 0x0C:
            gui.Printf((char*)"-");
            break;
        case 0x0D:
            gui.Printf((char*)"+");
            break;
        case 0x0E:
            gui.Printf((char*)"Backspace");
            break;
        case 0x0F:
            gui.Printf((char*)"Tab");
            break;
        case 0x10:
            gui.Printf((char*)"Q");
            break;
        case 0x11:
            gui.Printf((char*)"W");
            break;
        case 0x12:
            gui.Printf((char*)"E");
            break;
        case 0x13:
            gui.Printf((char*)"R");
            break;
        case 0x14:
            gui.Printf((char*)"T");
            break;
        case 0x15:
            gui.Printf((char*)"Y");
            break;
        case 0x16:
            gui.Printf((char*)"U");
            break;
        case 0x17:
            gui.Printf((char*)"I");
            break;
        case 0x18:
            gui.Printf((char*)"O");
            break;
        case 0x19:
            gui.Printf((char*)"P");
            break;
		case 0x1A:
			gui.Printf((char*)"[");
			break;
		case 0x1B:
			gui.Printf((char*)"]");
			break;
		case 0x1C:
			gui.Printf((char*)"ENTER");
			break;
		case 0x1D:
			gui.Printf((char*)"LCtrl");
			break;
		case 0x1E:
			gui.Printf((char*)"A");
			break;
		case 0x1F:
			gui.Printf((char*)"S");
			break;
        case 0x20:
            gui.Printf((char*)"D");
            break;
        case 0x21:
            gui.Printf((char*)"F");
            break;
        case 0x22:
            gui.Printf((char*)"G");
            break;
        case 0x23:
            gui.Printf((char*)"H");
            break;
        case 0x24:
            gui.Printf((char*)"J");
            break;
        case 0x25:
            gui.Printf((char*)"K");
            break;
        case 0x26:
            gui.Printf((char*)"L");
            break;
        case 0x27:
            gui.Printf((char*)";");
            break;
        case 0x28:
            gui.Printf((char*)"'");
            break;
        case 0x29:
            gui.Printf((char*)"`");
            break;
		case 0x2A:
			gui.Printf((char*)"LShift");
			break;
		case 0x2B:
			gui.Printf((char*)"\\");
			break;
		case 0x2C:
			gui.Printf((char*)"Z");
			break;
		case 0x2D:
			gui.Printf((char*)"X");
			break;
		case 0x2E:
			gui.Printf((char*)"C");
			break;
		case 0x2F:
			gui.Printf((char*)"V");
			break;
        case 0x30:
            gui.Printf((char*)"B");
            break;
        case 0x31:
            gui.Printf((char*)"N");
            break;
        case 0x32:
            gui.Printf((char*)"M");
            break;
        case 0x33:
            gui.Printf((char*)",");
            break;
        case 0x34:
            gui.Printf((char*)".");
            break;
        case 0x35:
            gui.Printf((char*)"/");
            break;
        case 0x36:
            gui.Printf((char*)"Rshift");
            break;
        case 0x37:
            gui.Printf((char*)"Keypad *");
            break;
        case 0x38:
            gui.Printf((char*)"LAlt");
            break;
        case 0x39:
            gui.Printf((char*)"Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (keycode <= 0x7f) {
                gui.Printf((char*)"Unknown key down");
            } else if (keycode <= 0x39 + 0x80) {
                gui.Printf((char*)"key up ");
				keycode -= 0x80;
                PrintLetter();
            } else gui.Printf((char*)"Unknown key up");
            break;
    }
}


///Register module
REGISTER_MODULE(new Application5(), (ModuleID::_application + 5), app_5);
