//###########################################################################
// vk_ps2_mouse.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_ps2_mouse.h"
#include "vk_event_codes.h"
#include "vk_kernel.h"


/// @brief Constructor
PS2Mouse::PS2Mouse()
    :ack(0),
    setting(0),
    mouseid(0),
    isLeftBtnPressed(false),
    isRightBtnPressed(false),
    isMiddleBtnPressed(false),
    work(NULL)
{
}


/// @brief Deconstructor
PS2Mouse::~PS2Mouse()
{
}


/// @brief Set data
/// @param data 
void PS2Mouse::SetData(void* data)
{
    config = *((Config*)data);
}


/// @brief Mouse write data
/// @param data 
/// @return ack
uint8_t PS2Mouse::MouseWriteData(uint8_t data)
{
    ps2.WriteCmd(PS2_CMD_WR_CTL_SEC_INPUT_BUFF);
    ps2.WriteData(data);
    return ps2.ReadData();
}


/// @brief Mouse read data
/// @return data
uint8_t PS2Mouse::MouseReadData()
{
    return ps2.ReadData();
}


/// @brief Configuure mouse
/// @return result
bool PS2Mouse::ConfigureMouse()
{
    //Disable irq
    kernel->system.DisableIRQ();

    //Read setting
    ps2.WriteCmd(PS2_CMD_READ_BYTE_0);
    setting = ps2.ReadData();
    
    //Set irq12 and ps2 clk enable flag
    setting |=  (PS2_CTL_SECOND_PORT_INT);
    setting &= ~(PS2_CTL_SECOND_PORT_CLK);

    //Enable irq12
    ps2.WriteCmd(PS2_CMD_WRITE_NEXT_BYTE_0);
    ps2.WriteData(setting);

    //Enable second ps2 port
    ps2.WriteCmd(PS2_CMD_ENA_SEC_PS2_PORT);

    //Restore to defaults
    MouseWriteData(PS2_MOUSE_CMD_SET_DEFAULTS);

    //Init/Detection Command Sequences
    MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
    MouseWriteData(200);

    MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
    MouseWriteData(100);

    MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
    MouseWriteData(80);

    MouseWriteData(PS2_MOUSE_CMD_GET_DEVICE_ID);
    mouseid = MouseReadData();

    //Enable 4th and 5th mouse buttons
    if (mouseid == 3)
    {
        MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
        MouseWriteData(200);

        MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
        MouseWriteData(200);

        MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
        MouseWriteData(80);

        MouseWriteData(PS2_MOUSE_CMD_GET_DEVICE_ID);
        mouseid = MouseReadData();
    }

    //Set sample rate
    MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
    MouseWriteData(200);

    //Set resolution
    MouseWriteData(PS2_MOUSE_CMD_SET_RESOLUTION);
    MouseWriteData(3);

    //Set scaling 1:1
    MouseWriteData(PS2_MOUSE_CMD_SCALING_1_1);

    //Enable mouse
    ack = MouseWriteData(PS2_MOUSE_CMD_ENA_DATA_REPORTING);

    //Enable irq
    kernel->system.EnableIRQ();

    return (0xfa == ack);
}


/// @brief Mouse input handler
void PS2Mouse::InputHandler()
{
    if (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)
    {
        packet.byte[count] = PortByteIn(PS2_READ_DATA);

        if (++count >= mouseid)
        {
            count = 0;
            kernel->workQueue.Sched(work);
        }
    }
}


/// @brief Mouse report handler
void PS2Mouse::ReportHandler()
{
    //Report left button
    if (packet.leftBtn && !isLeftBtnPressed)
    {
        isLeftBtnPressed = true;
        kernel->event.ReportKey(_BtnLeft, _KeyPressed);
    }
    else if (!packet.leftBtn && isLeftBtnPressed)
    {
        isLeftBtnPressed = false;
        kernel->event.ReportKey(_BtnLeft, _KeyReleased);
    }

    //Report right button
    if (packet.rightBtn && !isRightBtnPressed)
    {
        isRightBtnPressed = true;
        kernel->event.ReportKey(_BtnRight, _KeyPressed);
    }
    else if (!packet.rightBtn && isRightBtnPressed)
    {
        isRightBtnPressed = false;
        kernel->event.ReportKey(_BtnRight, _KeyReleased);
    }

    //Report middle button
    if (packet.middleBtn && !isMiddleBtnPressed)
    {
        isMiddleBtnPressed = true;
        kernel->event.ReportKey(_BtnMiddle, _KeyPressed);
    }
    else if (!packet.middleBtn && isMiddleBtnPressed)
    {
        isMiddleBtnPressed = false;
        kernel->event.ReportKey(_BtnMiddle, _KeyReleased);
    }

    //Report axis x, y, z movement value
    int axisX = (int16_t)packet.x - (packet.xSignBit ? 0x100 : 0);
    int axisY = (int16_t)packet.y - (packet.ySignBit ? 0x100 : 0);
    int axisZ = (int8_t)packet.z;
    kernel->event.ReportAxis(axisX, axisY, axisZ);
}


/// @brief Mouse open
bool PS2Mouse::Open()
{

    //Create work
    work = kernel->workQueue.Create((Method)&PS2Mouse::ReportHandler, this);

    //Set interrupt service
    kernel->interrupt.SetISR(config.irq, (Method)&PS2Mouse::InputHandler, this);

    //Config
    ConfigureMouse();

    return true;
}


/// @brief Mouse close
void PS2Mouse::Close()
{
    kernel->interrupt.RemoveISR(config.irq, (Method)(&PS2Mouse::InputHandler), this);
    kernel->workQueue.Delete(work);
}


/// @brief Probe
/// @param device 
/// @return 
bool PS2MouseDrv::Probe(PlatDevice* device)
{
    device->Attach(new PS2Mouse());
    kernel->device.RegisterInputDevice((InputDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool PS2MouseDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterInputDevice((InputDriver*)device->GetDriver());
    delete (PS2Mouse*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new PS2MouseDrv(), ps2mouse, ps2mouseDrv);
