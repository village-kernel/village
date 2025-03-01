//###########################################################################
// vk_dev_stream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_dev_stream.h"
#include "vk_kernel.h"


/// @brief Constructor
DevStream::DevStream(const char* name, int mode)
    :fopts(NULL)
{
    if (NULL != name) Open(name, mode);
}


/// @brief Destructor
DevStream::~DevStream()
{
}


/// @brief DevStream open
/// @param name 
/// @param mode 
/// @return 
bool DevStream::Open(const char* name, int mode)
{
    if (NULL == fopts)
    {
        fopts = kernel->device.GetDeviceFopts(name);
        if (NULL != fopts) return fopts->Open();
    }
    return false;
}


/// @brief DevStream write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int DevStream::Write(char* data, int size, int offset)
{
    if (NULL != fopts)
    {
        return fopts->Write((uint8_t*)data, size, offset);
    }
    return 0;
}


/// @brief DevStream read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int DevStream::Read(char* data, int size, int offset)
{
    if (NULL != fopts)
    {
        return fopts->Read((uint8_t*)data, size, offset);
    }
    return 0;
}


/// @brief DevStream io ctrl
/// @param cmd 
/// @param data 
/// @return 
int DevStream::IOCtrl(uint8_t cmd, void* data)
{
    if (NULL != fopts)
    {
        return fopts->IOCtrl(cmd, data);
    }
    return 0;
}


/// @brief DevStream close
void DevStream::Close()
{
    if (NULL != fopts)
    {
        fopts->Close();
    }
}
