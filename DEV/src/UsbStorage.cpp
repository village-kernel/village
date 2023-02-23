//###########################################################################
// UsbStorage.cpp
// Definitions of the functions that manage usb storage
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "UsbStorage.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "System.h"
#include "SpiFlash.h"
#include "SdCard.h"


///USB storage macro
#define STORAGE_LUN_NBR                  2
#define STORAGE_BLK_NBR                  1968
#define STORAGE_BLK_SIZ                  512
#define STORAGE_START_BLK                10


//Using spi flash
extern SpiFlash* fatfsFlash;
extern SdCard* fatfsSdCard;


///Override HAL_InitTick()
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;
}


///Override HAL_Delay()
void HAL_Delay(uint32_t Delay)
{
	System::DelayMs(Delay);
}


///USB storage init
static int8_t STORAGE_Init_FS(uint8_t lun)
{
	return (USBD_OK);
}


///USB storage get capacity
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t* block_num, uint16_t* block_size)
{
	switch (lun)
	{
		case 0:
			*block_num = STORAGE_BLK_NBR;
			*block_size = STORAGE_BLK_SIZ;
			break;
		case 1:
			*block_num = fatfsSdCard->GetSectorCount();
			*block_size = STORAGE_BLK_SIZ;
			break;
		default: return (USBD_FAIL);
	}

	return (USBD_OK);
}


///USB storage is ready
static int8_t STORAGE_IsReady_FS(uint8_t lun)
{
	return (USBD_OK);
}


///USB storage is write protected
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
	return (USBD_OK);
}


///USB storage read
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t* buf, uint32_t blk_addr, uint16_t blk_len)
{
	switch (lun)
	{
		case 0:
			for (uint32_t i = 0; i < blk_len; ++i)
			{
				uint32_t readByteSize = STORAGE_BLK_SIZ;
				uint32_t readAddress = (STORAGE_START_BLK + blk_addr + i) * STORAGE_BLK_SIZ;
				fatfsFlash->Read((uint8_t*)buf + (i * readByteSize), readByteSize, readAddress);
			}
			break;
		case 1:
			fatfsSdCard->Read(buf, blk_addr, blk_len);
			break;
		default: return (USBD_FAIL);
	}

	return (USBD_OK);
}


///USB storage write
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t* buf, uint32_t blk_addr, uint16_t blk_len)
{
	switch (lun)
	{
		case 0:
			for (uint32_t i = 0; i < blk_len; ++i)
			{
				uint32_t writeByteSize = STORAGE_BLK_SIZ;
				uint32_t writeAddress = (STORAGE_START_BLK + blk_addr + i) * STORAGE_BLK_SIZ;
				fatfsFlash->Write((uint8_t*)buf + (i * writeByteSize), writeByteSize, writeAddress);
			}
			break;
		case 1:
			fatfsSdCard->Write(buf, blk_addr, blk_len);
			break;
		default: return (USBD_FAIL);
	}

	return (USBD_OK);
}


///USB storage get max lun
static int8_t STORAGE_GetMaxLun_FS(void)
{
	return (STORAGE_LUN_NBR - 1);
}


///USB Mass storage Standard Inquiry Data
static const uint8_t STORAGE_Inquirydata_FS[] =
{
	//LUN 0
	0x00,
	0x80,
	0x02,
	0x02,
	(STANDARD_INQUIRY_DATA_LEN - 5),
	0x00,
	0x00,
	0x00,
	'V', 'K', ' ', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
	'v', 'i', 'l', 'l', 'a', 'g', 'e', ' ', /* Product      : 16 Bytes */
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
	//LUN 1
	0x00,
	0x80,
	0x02,
	0x02,
	(STANDARD_INQUIRY_DATA_LEN - 5),
	0x00,
	0x00,
	0x00,
	'V', 'K', ' ', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
	'v', 'i', 'l', 'l', 'a', 'g', 'e', ' ', /* Product      : 16 Bytes */
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	'0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
};


///USB storage interface fops fs
static USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
	STORAGE_Init_FS,
	STORAGE_GetCapacity_FS,
	STORAGE_IsReady_FS,
	STORAGE_IsWriteProtected_FS,
	STORAGE_Read_FS,
	STORAGE_Write_FS,
	STORAGE_GetMaxLun_FS,
	(int8_t*)STORAGE_Inquirydata_FS
};


///USB Device Core handle declaration
static USBD_HandleTypeDef hUsbDeviceFS;


///USB storage device initialize
void UsbStorage::Initialize()
{
#ifdef STM32H7xx
	//Select usb clock
	RCC->D2CCIP2R |= RCC_D2CCIP2R_USBSEL;

	//Enable USB Voltage detector
	PWR->CR3 |= PWR_CR3_USB33DEN;
#endif
	//Initialize usb device
	USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

	//Register usb class
	USBD_RegisterClass(&hUsbDeviceFS, &USBD_MSC);

	//Register usb storage
	USBD_MSC_RegisterStorage(&hUsbDeviceFS, &USBD_Storage_Interface_fops_FS);
}


///Start mount usb storage to pc
void UsbStorage::Mount()
{
	USBD_Start(&hUsbDeviceFS);
}


///Stop mount usb storage to pc
void UsbStorage::Unmount()
{
	USBD_Stop(&hUsbDeviceFS);
}
