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
//#include "spiFlash.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions of physical drive number for each drive */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 0 */


#define SPI_FLASH_BLOCK_SIZE        1
#define SPI_FLASH_SECTOR_SIZE       1968
#define SPI_FLASH_SECTOR_BYTE_SIZE  512
#define SPI_FLASH_START_SECTOR      10

//extern SpiFlash* fatfsFlash;

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	switch (pdrv) 
	{
		//case DEV_MMC: return fatfsFlash->IsFlashError() ? RES_ERROR : RES_OK;
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
	switch (pdrv)
	{
		case DEV_MMC: return RES_OK;
	}
	return STA_NOINIT;
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
	switch (pdrv)
	{
		case DEV_MMC:

			for (UINT i = 0; i < count; ++i)
			{
				uint32_t readByteSize = SPI_FLASH_SECTOR_BYTE_SIZE;
				uint32_t readAddress = (SPI_FLASH_START_SECTOR + sector + i) * SPI_FLASH_SECTOR_BYTE_SIZE;
				//fatfsFlash->Read((uint8_t*)buff + (i * readByteSize), readByteSize, readAddress);
			}

			//return fatfsFlash->IsFlashError() ? RES_ERROR : RES_OK;
	}
	return RES_PARERR;
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
	switch (pdrv)
	{
		case DEV_MMC:

			for (UINT i = 0; i < count; ++i)
			{
				uint32_t writeByteSize = SPI_FLASH_SECTOR_BYTE_SIZE;
				uint32_t writeAddress = (SPI_FLASH_START_SECTOR + sector + i) * SPI_FLASH_SECTOR_BYTE_SIZE;
				//fatfsFlash->Write((uint8_t*)buff + (i * writeByteSize), writeByteSize, writeAddress);
			}

			//return fatfsFlash->IsFlashError() ? RES_ERROR : RES_OK;
	}
	return RES_PARERR;
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
	DRESULT res;

	switch (pdrv)
	{
		case DEV_MMC:

			switch (cmd)
			{
				case CTRL_SYNC:
					res = RES_OK;
					break;

				case GET_SECTOR_SIZE:
					*(WORD*)buff = SPI_FLASH_SECTOR_BYTE_SIZE;
					res = RES_OK;
					break;

				case GET_BLOCK_SIZE:
					*(WORD*)buff = SPI_FLASH_BLOCK_SIZE;
					res = RES_OK;
					break;

				case GET_SECTOR_COUNT:
					*(DWORD*)buff = SPI_FLASH_SECTOR_SIZE;
					res = RES_OK;
					break;
			}

			return res;
	}
	return RES_PARERR;
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
