/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "stdlib.h"
#include "Device.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions of physical drive number for each drive */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_SD      1

/* Storage driver */
static Driver* storage[2] = { NULL };

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	switch (pdrv) 
	{
		case DEV_MMC: return RES_OK;
		case DEV_SD: return RES_OK;
	}
	return STA_NOINIT;
}

 

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	storage[pdrv] = device.GetDriver(DriverID::_storage + pdrv);
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	return (DRESULT)storage[pdrv]->Read((uint8_t*)buff, count, sector);
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	return (DRESULT)storage[pdrv]->Write((uint8_t*)buff, count, sector);
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return (DRESULT)storage[pdrv]->IOCtrl(cmd, (uint8_t*)buff);
}



/*-----------------------------------------------------------------------*/
/* Get fat time functions                                                */
/*-----------------------------------------------------------------------*/

DWORD get_fattime(void)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Fatfs malloc memory functions                                         */
/*-----------------------------------------------------------------------*/
#if FF_USE_LFN != 3
void* ff_memalloc(UINT mszie)
{
	return (void*)malloc(mszie);
}
#endif



/*-----------------------------------------------------------------------*/
/* Fatfs free memory functions                                           */
/*-----------------------------------------------------------------------*/
#if FF_USE_LFN != 3
void ff_memfree(void* mblock)
{
	free((void*)mblock);
}
#endif


#ifdef __cplusplus
}
#endif
