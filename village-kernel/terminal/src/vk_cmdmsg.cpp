//###########################################################################
// vk_cmdmsg.cpp
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//############################################################################
#include "vk_cmdmsg.h"
#include "vk_kernel.h"
#include "string.h"


/// @brief Constructor
CmdMsgMgr::CmdMsgMgr()
    :hasMessage(false),
    inputMode(_EDIT),
    txBufPos(0),
    rxBufPos(0),
    history(0)
{
    rxMsg.cmd = cmdBuffer;
}


/// @brief CmdMsgMgr initialize
/// @param driver 
void CmdMsgMgr::Setup(const char* driver)
{
    transceiver.Open(driver, FileMode::_ReadWrite);
}


/// @brief CmdMsgMgr execute
/// @return 
bool CmdMsgMgr::Execute()
{
    //Sent data when txbuffer not empty
    Sending();

    //Received data and decode
    return Receiving();
}


/// @brief CmdMsgMgr Exit
void CmdMsgMgr::Exit()
{
    transceiver.Close();
}


/// @brief CmdMsgMgr write
/// @param msg 
/// @param size 
void CmdMsgMgr::Write(uint8_t* msg, uint16_t size)
{
    //Calculate the size of msg
    size = (0 == size) ? strlen((const char*)msg) : size;

    //Copy msg data into txBuffer
    for (int i = 0; i < size; i++)
    {
        //The txBuffer is full, block here until the data is sent
        if (txBufPos >= arg_buffer_size) Sending();

        //Copy data
        txBuffer[txBufPos++] = msg[i];
    }

    //Sent data when txbuffer not empty
    Sending();
}


/// @brief Sent data when txbuffer not empty
/// @brief Reset txBufPos when sent data successfully
void CmdMsgMgr::Sending()
{
    if (txBufPos)
    {
        while (txBufPos != transceiver.Write((char*)txBuffer, txBufPos)) {}
        txBufPos = 0;
    }
}


/// @brief RecordTempCmd
void CmdMsgMgr::RecordTempCmd()
{
    //Return when history is not last
    if (cmd_history_size - 1 != history) return;

    //Release the last history memory space
    if (NULL != cmdHistory[cmd_history_size - 1]) delete[] cmdHistory[cmd_history_size - 1];

    //Alloc new history cmd memory
    uint8_t* historyCmd = new uint8_t[strlen((const char*)rxBuffer) + 1]();

    //Copy rxBuffer string to historyCmd 
    strcpy((char*)historyCmd, (const char*)rxBuffer);

    //Set the history cmd as the last history
    cmdHistory[cmd_history_size - 1] = historyCmd;
}


/// @brief Record history
void CmdMsgMgr::RecordHistory()
{
    //Alloc new history cmd memory
    uint8_t* historyCmd = new uint8_t[strlen((const char*)rxBuffer) + 1]();

    //Copy rxBuffer string to historyCmd 
    strcpy((char*)historyCmd, (const char*)rxBuffer);
    
    //Release the first history memory space
    if (NULL != cmdHistory[0]) delete[] cmdHistory[0];

    //Move cmdHistory[i+1] to cmdHistory[i]
    for (uint16_t i = 0; i < cmd_history_size - 2; i++)
    {
        cmdHistory[i] = cmdHistory[i+1];
    }

    //Set the history cmd as the second to last history
    cmdHistory[cmd_history_size - 2] = historyCmd;
    
    //Reset history position
    history = cmd_history_size - 1;
}


/// @brief Restored history
void CmdMsgMgr::RestoredHistory()
{
    //Return when history cmd is NULL
    if (NULL == cmdHistory[history]) return;

    //Clear display string
    for (uint16_t i = strlen((const char*)rxBuffer); i > 0; i--)
    {
        txBuffer[txBufPos++] = '\b';
        txBuffer[txBufPos++] = ' ';
        txBuffer[txBufPos++] = '\b';
    }

    //Reset history cmd to rxBuffer
    strcpy((char*)rxBuffer, (const char*)cmdHistory[history]);
    rxBufPos = strlen((const char*)rxBuffer);

    //Display new cmd
    for (uint16_t i = 0; i < rxBufPos; i++)
    {
        txBuffer[txBufPos++] = rxBuffer[i];
    }
}


/// @brief CmdMsgMgr receiving data and decode
/// @return 
bool CmdMsgMgr::Receiving()
{
    const uint8_t br_buf_size = 20;
    uint8_t brBuff[br_buf_size] = { 0 };
    uint8_t brSize = 0;

    while ((brSize = transceiver.Read((char*)brBuff, br_buf_size)) > 0)
    {
        for (uint8_t i = 0; i < brSize; i++)
        {
            uint8_t byte = brBuff[i];

            if (rxBufPos >= arg_buffer_size)
            {
                rxBufPos = 0;
                return false;
            }

            switch (inputMode)
            {
                case _INSERT: if (InsertMode(byte)) continue;
                case _EDIT:       EditMode(byte);   break;
                case _ANSI:       ANSIMode(byte);   break;
                case _DCS:        DCSMode(byte);    break;
                case _CSI:        CSIMode(byte);    break;
                case _OSC:        OSCMode(byte);    break;
                default:                            break;
            }

            if (true == hasMessage)
            {
                hasMessage = false;
                return true;
            }
        }
    }

    return false;
}


/// @brief Insert Mode
/// @param byte 
/// @return 
bool CmdMsgMgr::InsertMode(uint8_t byte)
{
    //ASCII 32(space) ~ 126(~)
    if (byte >= 0x20 && byte <= 0x7e)
    {
        //Move char[rxBufPos] to char[rxBufPos+1] and insert new char in char[rxBufPos]
        for (uint16_t i = strlen((const char*)rxBuffer); i > rxBufPos ; i--)
        {
            rxBuffer[i] = rxBuffer[i-1];
        }
        rxBuffer[rxBufPos++] = byte;
        
        //Sent new string
        uint16_t back = 0;
        txBuffer[txBufPos++] = byte;
        for (uint16_t i = rxBufPos; '\0' != rxBuffer[i]; i++)
        {
            txBuffer[txBufPos++] = rxBuffer[i];
            back++;
        }

        //Move cursor back
        for (uint16_t i = 0; i < back; i++)
        {
            txBuffer[txBufPos++] = '\b';
        }

        return true;
    }

    //ASCII DEL
    else if (0x7f == byte || '\b' == byte)
    {
        if (rxBufPos)
        {
            //Del char[rxBufPos] and move char[rxBufPos] to char[rxBufPos-1]
            rxBufPos--;
            for (uint16_t i = rxBufPos; '\0' != rxBuffer[i]; i++)
            {
                rxBuffer[i] = rxBuffer[i+1];
            }

            //Sent new string
            uint16_t back = 0;
            txBuffer[txBufPos++] = '\b';
            for (uint16_t i = rxBufPos; '\0' != rxBuffer[i]; i++)
            {
                txBuffer[txBufPos++] = rxBuffer[i];
                back++;
            }
            txBuffer[txBufPos++] = ' ';
            back++;

            //Move cursor back
            for (uint16_t i = 0; i < back; i++)
            {
                txBuffer[txBufPos++] = '\b';
            }
        }

        return true;
    }

    inputMode = _EDIT;

    return false;
}


/// @brief Edit Mode
/// @param byte 
/// @return 
void CmdMsgMgr::EditMode(uint8_t byte)
{
    //ANSI ESC
    if ('\033' == byte)
    {
        inputMode = _ANSI;
    }

    //ASCII 32(space) ~ 126(~)
    else if (byte >= 0x20 && byte <= 0x7e)
    {
        txBuffer[txBufPos++] = byte;
        rxBuffer[rxBufPos++] = byte;
        rxBuffer[rxBufPos+1] = '\0';
    }

    //ASCII DEL
    else if (0x7f == byte || '\b' == byte)
    {
        if (rxBufPos)
        {
            //Backspace one character
            rxBuffer[--rxBufPos] = '\0';

            //Backspace character on terminal
            txBuffer[txBufPos++] = '\b';
            txBuffer[txBufPos++] = ' ';
            txBuffer[txBufPos++] = '\b';
        }
    }

    //ASCII CR
    else if (0x0d == byte)
    {
        //Check is null cmd 
        if (rxBufPos <= 0)
        {
            strcpy((char*)cmdBuffer, "null");
            hasMessage = true;
            return;
        }

        //Set command
        for (uint16_t i = 0; ; i++)
        {
            if ((' '  == rxBuffer[i]) ||
                ('\r' == rxBuffer[i]) ||
                ('\0' == rxBuffer[i]))
            {
                cmdBuffer[i] = '\0'; break;
            }

            cmdBuffer[i] = rxBuffer[i];
        }

        //Record history
        RecordHistory();

        //Set args
        rxMsg.args = cmdHistory[cmd_history_size - 2];

        //Reset rxBufPos
        rxBufPos = 0;
        rxBuffer[rxBufPos] = '\0';
        hasMessage = true;
        return;
    }
}


/// @brief ANSI Mode
/// @param byte 
/// @return 
void CmdMsgMgr::ANSIMode(uint8_t byte)
{
    switch (byte)
    {
        case 'N': //ESC N | 0x8e | SS2 – Single Shift Two
            break;
        case 'O': //ESC O | 0x8f | SS3 – Single Shift Three
            break;
        case 'P': //ESC P | 0x90 | DCS – Device Control String
            inputMode = _DCS;
            break;
        case '[': //ESC [ | 0x9b | CSI - Control Sequence Introducer
            inputMode = _CSI;
            break;
        case '\\'://ESC \ | 0x9c | ST – String Terminator
            break;
        case ']': //ESC ] | 0x9d | OSC – Operating System Command
            inputMode = _OSC;
            break;
        case 'X': //ESC X | 0x98 | SOS – Start of String
            break;
        case '^': //ESC ^ | 0x9e | PM – Privacy Message
            break;
        case '_': //ESC _ | 0x9f | APC – Application Program Command
            break;
        case 'c': //ESC c |      | RIS – Reset to Initial State
            break;
        default: break;
    }
}


/// @brief DCS Mode
/// @param byte 
/// @return 
void CmdMsgMgr::DCSMode(uint8_t byte)
{

}


/// @brief CSI Mode
/// @param byte 
/// @return 
void CmdMsgMgr::CSIMode(uint8_t byte)
{
    //Param byte
    if (byte >= 0x30 && byte <= 0x3f)
    {

    }

    //Middle byte
    if (byte >= 0x20 && byte <= 0x2f)
    {

    }

    //Final byte
    if (byte >= 0x40 && byte <= 0x7e)
    {
        switch (byte)
        {
            case 'A': //up
                if (NULL != cmdHistory[history-1])
                {
                    RecordTempCmd();
                    history--;
                    RestoredHistory();
                }
                break;
            case 'B': //down
                if (history < cmd_history_size - 1)
                {
                    history++;
                    RestoredHistory();
                }
                break;
            case 'C': //right
                if ('\0' != rxBuffer[rxBufPos])
                {
                    txBuffer[txBufPos++] = rxBuffer[rxBufPos++];
                    inputMode = _INSERT;
                    return;
                }
                break;
            case 'D': //left
                if (rxBufPos)
                {
                    rxBufPos--;
                    txBuffer[txBufPos++] = '\b';
                    inputMode = _INSERT;
                    return;
                }
                break;
            case 'm': //SGR
                break;
            default: break;
        }

        inputMode = _EDIT;
    }
}


/// @brief OSC Mode
/// @param byte 
/// @return 
void CmdMsgMgr::OSCMode(uint8_t byte)
{
    if ('\0' == byte) inputMode = _EDIT;
}
