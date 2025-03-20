//###########################################################################
// vk_i2c_gt9xxx.cpp
// Definitions of the functions that manage gt9xxx touch ic
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_i2c_gt9xxx.h"
#include "vk_kernel.h"


/// @brief Constructor
GT9xxx::GT9xxx()
{
}


/// @brief Destructor
GT9xxx::~GT9xxx()
{
}


/// @brief SetData
/// @param data 
void GT9xxx::SetData(void* data)
{
    config = *((Config*)data);
}


/// @brief PinConfig
void GT9xxx::PinConfig()
{
    i2c.Initialize(config.i2cCfg);
    rstGpio.Initialize(config.rstGpio);
    intGpio.Initialize(config.intGpio);
}


/// @brief ExtiConfig
void GT9xxx::ExtiConfig()
{
    intGpio.ConfigPullType(Gpio::_NoPull);
    
    exti.Initialize(config.intGpio.pin);
    exti.ConfigExtPin(config.intGpio);
    exti.ConfigMode(Exti::_Interrupt);
    exti.ConfigTriggerEdge(Exti::_BothEdge);
    exti.EnableExtInterrupt(config.intirq);
}


/// @brief GetAck
/// @return 
bool GT9xxx::GetAck()
{
	if (I2c::Nack == i2c.GetAck())
	{
		i2c.Stop();
		return false;
	}
	return true;
}


/// @brief WriteReg
/// @param reg 
/// @param data 
/// @param size 
/// @return 
bool GT9xxx::WriteReg(uint16_t reg, uint8_t* data, uint8_t size)
{
    //send start condition
    i2c.Start();

    //send gt9xxx write cmd
    i2c.WriteByte(gt_wr_cmd);
    if (!GetAck()) return false;
    
    //send the high byte of reg
    i2c.WriteByte(reg >> 8);
    if (!GetAck()) return false;
    
    //send the low byte of reg
    i2c.WriteByte(reg & 0xff);
    if (!GetAck()) return false;

    //write data to ic
    for (uint8_t i = 0; i < size; i++)
    {
        i2c.WriteByte(data[i]);
        if (!GetAck()) return false;
    }

    //send stop condition
    i2c.Stop();
    return true;
}


/// @brief ReadReg
/// @param reg 
/// @param data 
/// @param size 
/// @return 
bool GT9xxx::ReadReg(uint16_t reg, uint8_t* data, uint8_t size)
{
    //send start condition
    i2c.Start();

    //send gt9xxx write cmd
    i2c.WriteByte(gt_wr_cmd);
    if (!GetAck()) return false;
    
    //send the high byte of reg
    i2c.WriteByte(reg >> 8);
    if (!GetAck()) return false;
    
    //send the low byte of reg
    i2c.WriteByte(reg & 0xff);
    if (!GetAck()) return false;
    //above is dummy write

    //send start condition
    i2c.Start();
    
    //send gt9xxx read cmd
    i2c.WriteByte(gt_rd_cmd);
    if (!GetAck()) return false;

    //read data from ic
    for (uint8_t i = 0; i < size; i++)
    {
        data[i] = i2c.ReadByte();
        if (i != (size - 1))
            i2c.PutAck(I2c::Ack);
        else
            i2c.PutAck(I2c::Nack);
    }

    //send stop condition
    i2c.Stop();
    return size;
}


/// @brief Reset IC
void GT9xxx::ResetIC()
{
    intGpio.Clear();
    rstGpio.Clear();
    kernel->system.DelayMs(10);
    rstGpio.Set();
    kernel->system.DelayMs(10);
}


/// @brief Check ID
/// @return 
bool GT9xxx::CheckID()
{
    char pid[5] = { 0 };

    if (ReadReg(gt_pid_reg, (uint8_t*)pid, 4))
    {
        if (0 == strcmp(pid, config.gt9xxxid)) return true;
    }

    return false;
}


/// @brief Exti input func
void GT9xxx::ExtiInputFunc()
{
    if (exti.Check())
    {
        kernel->workQueue.Sched(work);
        exti.Clear();
    }
}


/// @brief Scan work func
void GT9xxx::ScanWorkFunc()
{
    //Get status
    Status status;
    ReadReg(gt_status_reg, &status.value, 1);

    //Buffer ready
    if (status.buffer)
    {
        if (status.tpx)
        {
            //Calc gt_tpx_reg
            uint16_t gt_tpx_reg = gt_tp1_reg + ((status.tpx - 1) * sizeoftp);

            //Read touch point data
            TouchPoint tp;
            ReadReg(gt_tpx_reg, (uint8_t*)&tp, sizeoftp);

            //Debug info
            kernel->debug.Info("trackid: %d, x: %d, y: %d, tpx: %d", tp.trackid, tp.x, tp.y, status.tpx);
        }
    }

    //Clear status
    status.value = 0;
    WriteReg(gt_status_reg, &status.value, 1);
}


/// @brief Open
/// @return 
bool GT9xxx::Open()
{
    //Pin config
    PinConfig();

    //Reset ic
    ResetIC();

    //Check id
    if (!CheckID()) return false;

    //Soft reset ic
    uint8_t reset = 0x02;
    WriteReg(gt_ctl_reg, &reset, 1);

    //Wait for reset
    kernel->system.DelayMs(10);

    //End of reset
    uint8_t ended = 0;
    WriteReg(gt_ctl_reg, &ended, 1);

    //Create work
    work = kernel->workQueue.Create((Method)&GT9xxx::ScanWorkFunc, this);

    //Set interrupt service
    kernel->interrupt.AppendISR(config.intirq, (Method)&GT9xxx::ExtiInputFunc, this);

    //Exti config
    ExtiConfig();

    return true;
}


/// @brief Close
void GT9xxx::Close()
{
    exti.DisableExtInterrupt(config.intirq);
    kernel->interrupt.RemoveISR(config.intirq, (Method)(&GT9xxx::ExtiInputFunc), this);
    kernel->workQueue.Delete(work);
}


/// @brief Probe
/// @param device 
/// @return 
bool Gt9xxxDrv::Probe(PlatDevice* device)
{
    device->Attach(new GT9xxx());
    kernel->device.RegisterInputDevice((InputDriver*)device->GetDriver());
    return true;
}


/// @brief Remove
/// @param device 
/// @return 
bool Gt9xxxDrv::Remove(PlatDevice* device)
{
    kernel->device.UnregisterInputDevice((InputDriver*)device->GetDriver());
    delete (GT9xxx*)device->GetDriver();
    device->Detach();
    return true;
}


///Register driver
REGISTER_PLAT_DRIVER(new Gt9xxxDrv(), gt9xxx, gt9xxxDrv);
